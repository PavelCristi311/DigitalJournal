//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef ADDCOMMAND_H
#define ADDCOMMAND_H
#include "Command.h"

class AddCommand final : public Command {
    Repository* repo;
    DataEntry entry;
public:
    AddCommand(Repository* r, const DataEntry& e) : repo(r), entry(e) {}
    void execute() override { repo->add(entry); }
    void undo() override { repo->remove(entry.getDate()); }
};

#endif //ADDCOMMAND_H
