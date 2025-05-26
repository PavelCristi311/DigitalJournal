//
// Created by Cristian Pavel on 24.05.2025.
//

#include "JSONRepo.h"

void JSONRepo::load() {
    entries.clear();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    const QByteArray data = file.readAll();
    file.close();

    const QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray())
        return;
    for (QJsonArray arr = doc.array(); const QJsonValue val : arr) {
        if (!val.isObject())
            continue;
        QJsonObject obj = val.toObject();
        QString title = obj.value("title").toString();
        QString content = obj.value("content").toString();
        QString date = obj.value("date").toString();
        entries.emplace_back(title, content, date);
    }
}

void JSONRepo::save() const {
    QJsonArray arr;
    for (const auto& entry : entries) {
        QJsonObject obj;
        obj["title"] = entry.getTitle();
        obj["content"] = entry.getContent();
        obj["date"] = entry.getDate();
        arr.append(obj);
    }
    const QJsonDocument doc(arr);
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    file.write(doc.toJson());
    file.close();
}

void JSONRepo::add(const DataEntry &entry) {
    entries.push_back(entry);
    save();
}

void JSONRepo::remove(const QString &date) {
    const auto it = std::ranges::remove_if(entries,
        [&date](const DataEntry& e) { return e.getDate() == date; }).begin();
    entries.erase(it, entries.end());
    save();
}

void JSONRepo::update(const QString &date, const DataEntry &newData) {
    for (auto& entry : entries) {
        if (entry.getDate() == date) {
            entry = newData;
            break;
        }
    }
    save();
}

std::vector<DataEntry> JSONRepo::getAll() const {
    return entries;
}

void JSONRepo::sortByDate() {
    std::sort(entries.begin(), entries.end(),  [this](const DataEntry& a, const DataEntry& b) {
       const QDateTime dateA = parseJournalDate(a.getDate());
       const QDateTime dateB = parseJournalDate(b.getDate());
       return dateA > dateB;
   });
}