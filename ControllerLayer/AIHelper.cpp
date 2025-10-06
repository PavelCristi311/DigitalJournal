//
// Created by Cristian Pavel on 24.05.2025.
//

#include "AIHelper.h"
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QProcessEnvironment>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <algorithm>
#include <iostream>
#include <QFile>

AIHelper::AIHelper(QObject* parent) : QObject(parent) {
    connect(&networkManager, &QNetworkAccessManager::finished, this, &AIHelper::onReplyFinished);
    addMessage("system","You are Little Friend, a friendly AI companion. You have access to the user's journal entries which are provided below.Use this context to provide personalized responses.");
}

void AIHelper::addMessage(const QString& role, const QString& content) {
    QJsonObject msg;
    msg["role"] = role;
    msg["content"] = content;
    conversation.append(msg);
}

void AIHelper::setJournalEntries(const std::vector<DataEntry>& givenEntries) {
    journalEntries.clear();
    constexpr size_t maxEntries = 20;
    const size_t entryCount = std::min(maxEntries, givenEntries.size());
    journalEntries.reserve(entryCount);
    journalEntries.insert(journalEntries.end(),
                         givenEntries.begin(),
                         givenEntries.begin() + entryCount);
}

void AIHelper::sendMessage(const QString& userMessage) {
    qDebug() << "Sending message with journal context to Hugging Face Router (OpenAI-compatible)";
    addMessage("user", userMessage);

    QNetworkRequest request(QUrl("https://router.huggingface.co/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (qEnvironmentVariableIsEmpty("HUGGINGFACE_API_KEY")) {
        auto tryLoadEnv = [](const QString& path){
            QFile envFile(path);
            if (!envFile.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
            while (!envFile.atEnd()) {
                QString line = QString::fromUtf8(envFile.readLine()).trimmed();
                if (line.isEmpty() || line.startsWith('#')) continue;
                const int eq = line.indexOf('=');
                if (eq <= 0) continue;
                const QString key = line.left(eq).trimmed();
                const QString val = line.mid(eq + 1).trimmed();
                if (!key.isEmpty()) qputenv(key.toUtf8(), val.toUtf8());
            }
            envFile.close();
            return true;
        };
        const QString appDir = QCoreApplication::applicationDirPath();
        const QString curDir = QDir::currentPath();
        const QString parentDir = QDir(curDir).absoluteFilePath("..");
        if (!tryLoadEnv(QDir(appDir).filePath(".env"))) {
            if (!tryLoadEnv(QDir(curDir).filePath(".env"))) {
                tryLoadEnv(QDir(parentDir).filePath(".env"));
            }
        }
    }

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString apiKey = env.value("HUGGINGFACE_API_KEY").trimmed();
    if (!apiKey.isEmpty()) {
        qDebug() << "Loaded HF key prefix:" << (apiKey.startsWith("Bearer ") ? QString("Bear") : apiKey.left(4) + "****");
    }
    if (apiKey.startsWith("Bearer ")) apiKey = apiKey.mid(7).trimmed();
    if (apiKey.isEmpty()) {
        qWarning() << "Missing HUGGINGFACE_API_KEY";
        emit replyReceived("Config error: missing HUGGINGFACE_API_KEY.");
        return;
    }
    request.setRawHeader("Authorization", QByteArray("Bearer ") + apiKey.toUtf8());
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "DigitalJournal/1.0 (Qt)");
    request.setRawHeader("x-wait-for-model", "true");

    QString journalContext = "JOURNAL ENTRIES:\n\n";
    for (const auto& entry : journalEntries) {
        journalContext += "Date: " + entry.getDate() + "\n";
        journalContext += "Title: " + entry.getTitle() + "\n";
        journalContext += "Content: " + entry.getContent() + "\n\n";
    }

    QJsonObject body;
    body["model"] = QStringLiteral("deepseek-ai/DeepSeek-V3.2-Exp:novita");

    QJsonArray chatMsgs = conversation;
    QJsonObject ctxMsg;
    ctxMsg["role"] = "system";
    ctxMsg["content"] = journalContext;
    chatMsgs.append(ctxMsg);

    body["messages"] = chatMsgs;
    body["temperature"] = 0.7;
    body["max_tokens"] = 256;
    body["stream"] = false;
    QByteArray jsonData = QJsonDocument(body).toJson();
    qDebug() << "Request payload size: " << jsonData.size();
    networkManager.post(request, jsonData);
}

void AIHelper::onReplyFinished(QNetworkReply* reply) {
    if (!reply) {
        emit replyReceived("Error: Invalid network response");
        return;
    }

    const QByteArray response = reply->readAll();

    if (reply->error() == QNetworkReply::NoError) {
        QJsonParseError jsonError;
        const QJsonDocument doc = QJsonDocument::fromJson(response, &jsonError);

        if (jsonError.error != QJsonParseError::NoError) {
            emit replyReceived("Error parsing response: " + jsonError.errorString());
        } else if (doc.isObject()) {
            QString aiReply;
            auto obj = doc.object();

            if (auto choices = obj["choices"].toArray(); !choices.isEmpty()) {
                if (QJsonObject messageObj = choices[0].toObject()["message"].toObject(); !messageObj.isEmpty()) {
                    aiReply = messageObj["content"].toString();

                    addMessage("assistant", aiReply);
                }
            }

            if (aiReply.isEmpty()) {
                aiReply = "Received empty response from API";
            }
            emit replyReceived(aiReply);
        } else {
            emit replyReceived("Error: Unexpected response format");
        }
    } else {
        const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        emit replyReceived(QString("Network error (%1): %2\nBody: %3")
                           .arg(status)
                           .arg(reply->errorString())
                           .arg(QString::fromUtf8(response)));
    }

    reply->deleteLater();
}