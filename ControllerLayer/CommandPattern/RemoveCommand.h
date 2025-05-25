//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef REMOVECOMMAND_H
#define REMOVECOMMAND_H
#include "Command.h"

#include <utility>
class RemoveCommand final : public Command {
    Repository* repo;
    DataEntry removedEntry;
    QString date;
public:
    RemoveCommand(Repository* r, QString  d): repo(r), removedEntry("", "", "") ,date(std::move(d)){
        for (const auto all = repo->getAll(); const auto& e : all)
            if (e.getDate() == date)
                removedEntry = e;
    }
    void execute() override { repo->remove(date); }
    void undo() override { repo->add(removedEntry); }
};

#endif //REMOVECOMMAND_H
