//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef AIHELPER_H
#define AIHELPER_H
#pragma once
#include <QJsonArray>
#include <QObject>
#include <QNetworkReply>
#include "../RepositoryLayer/DataEntry.h"

class AIHelper : public QObject {
    Q_OBJECT
public:
    explicit AIHelper(QObject* parent = nullptr);
    void addMessage(const QString& role, const QString& content);
    void sendMessage(const QString& userMessage);
    void setJournalEntries(const std::vector<DataEntry>& givenEntries);
    [[nodiscard]] unsigned long getJEsize() const {
    return journalEntries.size();}
signals:
    void replyReceived(const QString& reply);
private slots:
    void onReplyFinished(QNetworkReply* reply);
private:
    QNetworkAccessManager networkManager;
    QJsonArray conversation;
protected:
    std::vector<DataEntry> journalEntries;
};

#endif //AIHELPER_H
