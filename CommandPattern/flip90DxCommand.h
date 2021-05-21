#ifndef IMAGE_EDITOR_FLIP90DXCOMMAND_H
#define IMAGE_EDITOR_FLIP90DXCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class flip90DxCommand : public ICommand {
private:
    Image &image;
    Pixel *bakData;

public:
    explicit flip90DxCommand(Image &image);

    ~flip90DxCommand() override;

    void execute() override;

    void undo() override;

    void redo() override;
};


#endif
