//
// Created by jacopo on 15/05/21.
//

#include "CommandManager.h"

void CommandManager::execute(std::shared_ptr<ICommand> command) {
    redoStack = commandStack(); //clear stack
    command->execute();
    undoStack.push(command);
}

void CommandManager::undo() {
    if (undoStack.empty())
        return;

    undoStack.top()->undo();
    redoStack.push(undoStack.top());
    undoStack.pop();
}

void CommandManager::redo() {
    if (redoStack.empty())
        return;

    redoStack.top()->redo();
    undoStack.push(redoStack.top());
    redoStack.pop();
}
