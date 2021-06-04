#ifndef IMAGE_EDITOR_COLORMASKCOMMAND_H
#define IMAGE_EDITOR_COLORMASKCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class colorMaskCommand : public ICommand {
private:
    Image &image;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;
    int r, g, b;

public:
    explicit colorMaskCommand(Image &, int r, int g, int b);

    void execute() override;

    void undo() override;

    void redo() override;

    void colorMask();
};


#endif
