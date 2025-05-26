//
// Created by Cristian Pavel on 24.05.2025.
//

#include "Controller.h"
Controller::Controller(Repository* repository) : repo(repository) {}
void Controller::add(const DataEntry& entry) {
    auto cmd = std::make_unique<AddCommand>(repo, entry);
    cmd->execute();
    undoStack.push(std::move(cmd));
    while (!redoStack.empty()) redoStack.pop();
}
void Controller::remove(const QString& date) {
    auto cmd = std::make_unique<RemoveCommand>(repo, date);
    cmd->execute();
    undoStack.push(std::move(cmd));
    while (!redoStack.empty()) redoStack.pop();
}
void Controller::update(const QString& date, const DataEntry& newData) {
    auto cmd = std::make_unique<UpdateCommand>(repo, date, newData);
    cmd->execute();
    undoStack.push(std::move(cmd));
    while (!redoStack.empty()) redoStack.pop();
}
void Controller::undo() {
    if (!undoStack.empty()) {
        auto& cmd = undoStack.top();
        cmd->undo();
        redoStack.push(std::move(cmd));
        undoStack.pop();
    }
}
void Controller::redo() {
    if (!redoStack.empty()) {
        auto& cmd = redoStack.top();
        cmd->execute();
        undoStack.push(std::move(cmd));
        redoStack.pop();
    }
}
std::vector<DataEntry> Controller::filter(const FilterStrategy& strategy) const {
    return strategy.filter(repo->getAll());
}

std::vector<DataEntry> Controller::getAll() const {
    return repo->getAll();
}

bool Controller::canUndo() const {
    return !undoStack.empty();
}
bool Controller::canRedo() const {
    return !redoStack.empty();
}

void Controller::sortAll() const {
    repo->sortByDate();
}
