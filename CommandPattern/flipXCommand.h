#ifndef IMAGE_EDITOR_FLIPXCOMMAND_H
#define IMAGE_EDITOR_FLIPXCOMMAND_H

#include "../Image.h"
#include "ICommand.h"

class flipXCommand:public ICommand {

private:
    Image& image;
    Pixel* bakData;

public:
    explicit flipXCommand(Image& image);
    ~flipXCommand() override;

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
