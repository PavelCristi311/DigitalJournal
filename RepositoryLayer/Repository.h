//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include "DataEntry.h"
#include <utility>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

class Repository {
protected:
    std::vector<DataEntry> entries;
    QString filename;
    virtual void load() = 0;
    virtual void save() const = 0;
public:
    explicit Repository(QString givenFilename) : filename(std::move(givenFilename)) {}
    virtual ~Repository() = default;
    virtual void add(const DataEntry& entry) = 0;
    virtual void remove(const QString& date) = 0;
    virtual void update(const QString& date, const DataEntry& newData) = 0;
    [[nodiscard]] virtual std::vector<DataEntry> getAll() const = 0;
    virtual void sortByDate()=0;
    static QDateTime parseJournalDate(const QString& dateString) {
        QStringList parts = dateString.split(" / ");
        if (parts.size() != 2) {
            return {};
        }
        const QString& timeStr = parts[0];
        const QString& dateStr = parts[1];
        const QString fullDateTimeStr = dateStr + " " + timeStr;
        return QDateTime::fromString(fullDateTimeStr, "dd.MM.yyyy hh:mm:ss");
    }
};



#endif //REPOSITORY_H
