#ifndef IMAGE_EDITOR_COLORMASKCOMMAND_H
#define IMAGE_EDITOR_COLORMASKCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class colorMaskCommand: public ICommand {
private:
    Image& image;
    Pixel* bakData;
    int r, g, b;

public:
    explicit colorMaskCommand(Image&, int r, int g, int b);
    ~colorMaskCommand() override;

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
