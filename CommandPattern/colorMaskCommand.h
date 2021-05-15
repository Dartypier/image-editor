#ifndef IMAGE_EDITOR_COLORMASKCOMMAND_H
#define IMAGE_EDITOR_COLORMASKCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class colorMaskCommand: public ICommand {
private:
    Image& image;
    Color* bakData;
    int r, g, b;

public:
    colorMaskCommand(Image&, int r, int g, int b);
    ~colorMaskCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
