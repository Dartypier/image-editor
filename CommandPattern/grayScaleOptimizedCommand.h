#ifndef IMAGE_EDITOR_GRAYSCALEOPTIMIZEDCOMMAND_H
#define IMAGE_EDITOR_GRAYSCALEOPTIMIZEDCOMMAND_H

#include "ICommand.h"
#include "../Image.h"

class grayScaleOptimizedCommand : public ICommand {
private:
    Image &image;
    Pixel *bakData;

public:
    explicit grayScaleOptimizedCommand(Image &image);

    ~grayScaleOptimizedCommand() override;

    void execute() override;

    void undo() override;

    void redo() override;
};


#endif //IMAGE_EDITOR_GRAYSCALEOPTIMIZEDCOMMAND_H
