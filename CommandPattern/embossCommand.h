#ifndef IMAGE_EDITOR_EMBOSSCOMMAND_H
#define IMAGE_EDITOR_EMBOSSCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class embossCommand : public ICommand{
private:
    Image& image;
    Pixel* bakData;

public:
    explicit embossCommand(Image& image);
    ~embossCommand() override;

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
