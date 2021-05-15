//
// Created by jacopo on 15/05/21.
//

#include "colorMaskCommand.h"

colorMaskCommand::colorMaskCommand(Image &image, int r, int g, int b) :
    image(image), r(r), g(g), b(b)
{
    bakData = image.getDeepData();
}

colorMaskCommand::~colorMaskCommand() {
    delete bakData;
}

void colorMaskCommand::execute() {
    image.colorMask(r, g, b);
}

void colorMaskCommand::undo() {
    image.setDeepData(bakData);
}

void colorMaskCommand::redo() {
    execute();
}
