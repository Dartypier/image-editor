#ifndef IMAGE_EDITOR_SHARPENCOMMAND_H
#define IMAGE_EDITOR_SHARPENCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class sharpenCommand : public ICommand {
private:
    Image &image;
    std::vector<Pixel>& pixelBuffer;
    std::vector<Pixel> backupPixelBuffer;

    void sharpen();

public:
    explicit sharpenCommand(Image &image);

    void execute() override;

    void undo() override;

    void redo() override;
};


#endif
