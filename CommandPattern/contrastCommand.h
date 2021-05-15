#ifndef IMAGE_EDITOR_CONTRASTCOMMAND_H
#define IMAGE_EDITOR_CONTRASTCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class contrastCommand : public ICommand{
private:
    Image& image;
    Color* bakData;
    int contrast;

public:
    contrastCommand(Image& image, int conrast);
    ~contrastCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
