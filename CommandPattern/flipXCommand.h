#ifndef IMAGE_EDITOR_FLIPXCOMMAND_H
#define IMAGE_EDITOR_FLIPXCOMMAND_H

#include "../Image.h"
#include "ICommand.h"

class flipXCommand:public ICommand {

private:
    Image& image;
    Color* bakData;

public:
    flipXCommand(Image& image);
    ~flipXCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
