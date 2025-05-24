//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef UPDATECOMMAND_H
#define UPDATECOMMAND_H
#include "Command.h"
class RemoveCommand final : public Command {
    Repository* repo;
    DataEntry removedEntry;
    QString date;
public:
    RemoveCommand(Repository* r, const QString& d): repo(r), date(d) {
        auto all = repo->getAll();
        for (const auto& e : all)
            if (e.getDate() == date)
                removedEntry = e;
    }
    void execute() override { repo->remove(date); }
    void undo() override { repo->add(removedEntry); }
};
#endif //UPDATECOMMAND_H
