#ifndef IMAGE_EDITOR_SCALECOMMAND_H
#define IMAGE_EDITOR_SCALECOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class scaleCommand : public ICommand {
private:
    Image &image;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;
    int backupW;
    int backupH;
    int x;
    int y;

    void scale();

public:
    scaleCommand(Image &image, int x, int y);

    void execute() override;

    void undo() override;

    void redo() override;
};


#endif
