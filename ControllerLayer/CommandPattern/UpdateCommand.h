//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef UPDATECOMMAND_H
#define UPDATECOMMAND_H
#include "Command.h"
class UpdateCommand final : public Command {
    Repository* repo;
    DataEntry oldEntry, newEntry;
    QString date;
public:
    UpdateCommand(Repository* r, const QString& d, const DataEntry& n)
        : repo(r), newEntry(n), date(d), oldEntry("", "", "") {
        auto all = repo->getAll();
        for (const auto& e : all)
            if (e.getDate() == date)
                oldEntry = e;
    }
    void execute() override { repo->update(date, newEntry); }
    void undo() override { repo->update(date, oldEntry); }
};
#endif //UPDATECOMMAND_H
