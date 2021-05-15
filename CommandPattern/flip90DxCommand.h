#ifndef IMAGE_EDITOR_FLIP90DXCOMMAND_H
#define IMAGE_EDITOR_FLIP90DXCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class flip90DxCommand : public ICommand{
private:
    Image& image;
    Color* bakData;

public:
    flip90DxCommand(Image& image);
    ~flip90DxCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
