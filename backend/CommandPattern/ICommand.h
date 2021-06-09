#ifndef IMAGE_EDITOR_ICOMMAND_H
#define IMAGE_EDITOR_ICOMMAND_H

class ICommand {
public:
    virtual void execute() = 0;

    virtual void undo() = 0;

    virtual void redo() = 0;

    virtual ~ICommand() = default;
};

#endif //IMAGE_EDITOR_ICOMMAND_H
