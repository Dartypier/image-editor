#ifndef IMAGE_EDITOR_SHARPENCOMMAND_H
#define IMAGE_EDITOR_SHARPENCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class sharpenCommand :public ICommand{
private:
    Image& image;
    Color* bakData;

public:
    sharpenCommand(Image& image);
    ~sharpenCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
