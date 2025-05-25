//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef UPDATECOMMAND_H
#define UPDATECOMMAND_H
#include "Command.h"

#include <utility>
class UpdateCommand final : public Command {
    Repository* repo;
    DataEntry oldEntry, newEntry;
    QString date;
public:
    UpdateCommand(Repository* r, QString  d, DataEntry  n): repo(r), oldEntry("", "", ""), newEntry(std::move(n)), date(std::move(d)) {
        for (const auto all = repo->getAll(); const auto& e : all)
            if (e.getDate() == date)
                oldEntry = e;
    }
    void execute() override { repo->update(date, newEntry); }
    void undo() override { repo->update(date, oldEntry); }
};
#endif //UPDATECOMMAND_H
