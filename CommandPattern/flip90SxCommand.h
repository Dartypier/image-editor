#ifndef IMAGE_EDITOR_FLIP90SXCOMMAND_H
#define IMAGE_EDITOR_FLIP90SXCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class flip90SxCommand:public ICommand {
private:
    Image& image;
    Color* bakData;

public:
    flip90SxCommand(Image& image);
    ~flip90SxCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
