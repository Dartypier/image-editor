#ifndef IMAGE_EDITOR_FLIPYCOMMAND_H
#define IMAGE_EDITOR_FLIPYCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class flipYCommand : public ICommand{
private:
    Image& image;
    Color* bakData;

public:
    flipYCommand(Image& image);
    ~flipYCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
