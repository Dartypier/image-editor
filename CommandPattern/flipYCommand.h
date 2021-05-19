#ifndef IMAGE_EDITOR_FLIPYCOMMAND_H
#define IMAGE_EDITOR_FLIPYCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class flipYCommand : public ICommand{
private:
    Image& image;
    Pixel* bakData;

public:
    explicit flipYCommand(Image& image);
    ~flipYCommand() override;

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
