//
// Created by Cristian Pavel on 24.05.2025.
//

#include "CSVRepo.h"
void CSVRepo::load() {
    entries.clear();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split('|');
        if (parts.size() != 3)
            continue;
        entries.emplace_back(parts[0], parts[1], parts[2]);
    }
    file.close();
}
void CSVRepo::save() const {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    for (const auto& entry : entries) {
        out << entry.getTitle() << "|" << entry.getContent() << "|" << entry.getDate() << "\n";
    }
    file.close();
}
void CSVRepo::add(const DataEntry &entry) {
    entries.push_back(entry);
    save();
}
void CSVRepo::remove(const QString &date) {
    const auto it = std::ranges::remove_if(entries,
                                           [&date](const DataEntry& e) { return e.getDate() == date; }).begin();
    entries.erase(it, entries.end());
    save();
}
void CSVRepo::update(const QString &date, const DataEntry &newData) {
    for (auto& entry : entries) {
        if (entry.getDate() == date) {
            entry = newData;
            break;
        }
    }
    save();
}
std::vector<DataEntry> CSVRepo::getAll() const {
    return entries;
}


