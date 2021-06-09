//
// Created by jacopo on 15/05/21.
//

#include "CommandManager.h"

void CommandManager::execute(const std::shared_ptr<ICommand>& command) {
    redoStack = commandStack(); //clear stack
    command->execute();
    undoStack.push(command);
}

void CommandManager::undo() {
    if (!undoStack.empty()) {
        undoStack.top()->undo();
        redoStack.push(undoStack.top());
        undoStack.pop();
    }
}

void CommandManager::redo() {
    if (!redoStack.empty()) {
        redoStack.top()->redo();
        undoStack.push(redoStack.top());
        redoStack.pop();
    }
}

bool CommandManager::isUndoStackEmpty() {
    if(undoStack.empty())
        return true;
    else
        return false;
}

bool CommandManager::isRedoStackEmpty() {
    if(redoStack.empty())
        return true;
    else
        return false;
}
