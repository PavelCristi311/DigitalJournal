//
// Created by Cristian Pavel on 24.05.2025.
//

#include "AIHelper.h"
#include <QProcess>
#include <QCoreApplication>
#include <QDir>
#include <QDebug>
#include <QProcessEnvironment>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include "../API_KEY.h"

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
    journalEntries = givenEntries;
}

void AIHelper::sendMessage(const QString& userMessage) {
    qDebug() << "Sending message with journal context to Groq API";

    addMessage("user", userMessage);

    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setPeerVerifyMode(QSslSocket::VerifyNone);

    QNetworkRequest request(QUrl("https://api.groq.com/openai/v1/chat/completions"));
    request.setSslConfiguration(sslConfig);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    API_KEY key;
    request.setRawHeader("Authorization", key.getKey().data());

    QString journalContext = "JOURNAL ENTRIES:\n\n";
    for (const auto& entry : journalEntries) {
        journalContext += "Date: " + entry.getDate() + "\n";
        journalContext += "Title: " + entry.getTitle() + "\n";
        journalContext += "Content: " + entry.getContent() + "\n\n";
    }

    QJsonArray messages = conversation;

    QJsonObject journalContextMsg;
    journalContextMsg["role"] = "system";
    journalContextMsg["content"] = journalContext;
    messages.append(journalContextMsg);

    QJsonObject body;
    body["model"] = "llama3-8b-8192";
    body["messages"] = messages;

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
        const QString errorMessage = "Network error: " + reply->errorString();
        emit replyReceived(errorMessage);
    }

    reply->deleteLater();
}