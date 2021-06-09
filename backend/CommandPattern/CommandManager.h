//
// Created by jacopo on 15/05/21.
//

#ifndef IMAGE_EDITOR_COMMANDMANAGER_H
#define IMAGE_EDITOR_COMMANDMANAGER_H

#include <stack>
#include "ICommand.h"
#include <memory>

typedef std::stack<std::shared_ptr<ICommand>> commandStack;

class CommandManager {

private:
    commandStack undoStack;
    commandStack redoStack;

public:
    void execute(const std::shared_ptr<ICommand>& command);

    void undo();

    void redo();

    bool isUndoStackEmpty();
    bool isRedoStackEmpty();
};


#endif //IMAGE_EDITOR_COMMANDMANAGER_H
