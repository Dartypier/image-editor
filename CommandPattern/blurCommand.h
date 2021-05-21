#ifndef IMAGE_EDITOR_BLURCOMMAND_H
#define IMAGE_EDITOR_BLURCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class blurCommand : public ICommand {
private:
    Image &image;
    Pixel *bakData;

public:
    explicit blurCommand(Image &image);

    ~blurCommand() override;

    void execute() override;

    void undo() override;

    void redo() override;
};


#endif
