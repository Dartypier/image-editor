#ifndef IMAGE_EDITOR_BRIGHTNESSCOMMAND_H
#define IMAGE_EDITOR_BRIGHTNESSCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class brightnessCommand : public ICommand {
private:
    Image& image;
    Pixel* bakData;
    int value;

public:
    explicit brightnessCommand(Image& image, int value);
    ~brightnessCommand() override;

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
