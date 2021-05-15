#ifndef IMAGE_EDITOR_SCALECOMMAND_H
#define IMAGE_EDITOR_SCALECOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class scaleCommand : public ICommand{
private:
    Image& image;
    Color* bakData;
    int percentual{0}, x{0}, y{0};

public:
    scaleCommand(Image& image, int percentual);
    scaleCommand(Image& image, int x, int y);
    ~scaleCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
