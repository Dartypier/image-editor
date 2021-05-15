#ifndef IMAGE_EDITOR_BRIGHTNESSCOMMAND_H
#define IMAGE_EDITOR_BRIGHTNESSCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class brightnessCommand : public ICommand {
private:
    Image& image;
    Color* bakData;
    int value;

public:
    brightnessCommand(Image& image, int value);
    ~brightnessCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
