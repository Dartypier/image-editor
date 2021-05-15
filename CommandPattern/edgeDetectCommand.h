#ifndef IMAGE_EDITOR_EDGEDETECTCOMMAND_H
#define IMAGE_EDITOR_EDGEDETECTCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class edgeDetectCommand : public ICommand{
private:
    Image& image;
    Color* bakData;

public:
    edgeDetectCommand(Image& image);
    ~edgeDetectCommand();

    void execute() override;
    void undo() override;
    void redo() override;
};


#endif
