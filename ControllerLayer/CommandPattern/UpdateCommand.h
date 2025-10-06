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
    QString oldDate;
    QString newDate;
public:
    UpdateCommand(Repository* r,QString  date,const DataEntry& updated): repo(r), oldEntry("","",""), newEntry(updated),oldDate(std::move(date)),newDate(updated.getDate()) {
        for (auto &e: repo->getAll())
            if (e.getDate() == oldDate) {
                oldEntry = e;
                break;
            }
    }

    void execute() override { repo->update(oldDate, newEntry);; }
    void undo() override { repo->update(newDate, oldEntry); }
};
#endif //UPDATECOMMAND_H
