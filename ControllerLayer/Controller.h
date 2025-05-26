//
// Created by Cristian Pavel on 24.05.2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../RepositoryLayer/Repository.h"
#include "CommandPattern/AddCommand.h"
#include "CommandPattern/RemoveCommand.h"
#include "CommandPattern/UpdateCommand.h"
#include "FilterStrategy/AndFilterStrategy.h"
#include "FilterStrategy/OrFilterStrategy.h"

class Controller {
    Repository* repo;
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;
public:
    explicit Controller(Repository* repository);

    void add(const DataEntry& entry);
    void remove(const QString& date);
    void update(const QString& date, const DataEntry& newData);

    void undo();
    void redo();

    [[nodiscard]] bool canUndo() const;
    [[nodiscard]] bool canRedo() const;

    [[nodiscard]] std::vector<DataEntry> filter(const FilterStrategy& strategy) const;
    [[nodiscard]] std::vector<DataEntry> getAll() const;
    void sortAll() const;
};


#endif //CONTROLLER_H
