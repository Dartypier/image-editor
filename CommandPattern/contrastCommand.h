#ifndef IMAGE_EDITOR_CONTRASTCOMMAND_H
#define IMAGE_EDITOR_CONTRASTCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class contrastCommand : public ICommand{
private:
    Image& image;
    Pixel* bakData;
    int contrast;

public:
    explicit contrastCommand(Image& image, int conrast);
    ~contrastCommand() override;

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
