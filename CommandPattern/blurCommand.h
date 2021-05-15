#ifndef IMAGE_EDITOR_BLURCOMMAND_H
#define IMAGE_EDITOR_BLURCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class blurCommand : public ICommand{
private:
    Image& image;
    Color* bakData;

public:
    blurCommand(Image& image);
    ~blurCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
