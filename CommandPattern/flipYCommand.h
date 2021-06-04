#ifndef IMAGE_EDITOR_FLIPYCOMMAND_H
#define IMAGE_EDITOR_FLIPYCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class flipYCommand : public ICommand {
private:
    Image &image;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;

public:
    explicit flipYCommand(Image &image);

    void execute() override;

    void undo() override;

    void redo() override;

    void flipY();
};


#endif
