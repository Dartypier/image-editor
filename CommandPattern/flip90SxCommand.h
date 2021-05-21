#ifndef IMAGE_EDITOR_FLIP90SXCOMMAND_H
#define IMAGE_EDITOR_FLIP90SXCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class flip90SxCommand : public ICommand {
private:
    Image &image;
    Pixel *bakData;

public:
    explicit flip90SxCommand(Image &image);

    ~flip90SxCommand() override;

    void execute() override;

    void undo() override;

    void redo() override;
};


#endif
