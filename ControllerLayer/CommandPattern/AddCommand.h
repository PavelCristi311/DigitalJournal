//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H
#include "Command.h"

#include <utility>

class AddCommand final : public Command {
    Repository* repo;
    DataEntry entry;
public:
    AddCommand(Repository* r, DataEntry  e) : repo(r), entry(std::move(e)) {}
    void execute() override { repo->add(entry); }
    void undo() override { repo->remove(entry.getDate()); }
};

#endif //ADDCOMMAND_H
