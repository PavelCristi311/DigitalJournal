//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef COMMAND_H
#define COMMAND_H
#include "../../RepositoryLayer/DataEntry.h"
#include "../../RepositoryLayer/Repository.h"
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

#endif //COMMAND_H
