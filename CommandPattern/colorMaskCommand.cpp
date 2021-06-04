//
// Created by jacopo on 15/05/21.
//

#include "colorMaskCommand.h"

colorMaskCommand::colorMaskCommand(Image &image, int r, int g, int b) :
        image(image), r(r), g(g), b(b) , pixelBuffer(image.getPixelBuffer()){
    backupPixelBuffer = pixelBuffer;
}

void colorMaskCommand::execute() {
    colorMask();
}

void colorMaskCommand::undo() {
    pixelBuffer = backupPixelBuffer;
}

void colorMaskCommand::redo() {
    execute();
}

void colorMaskCommand::colorMask() {

    for (int i = 0; i < image.getSize(); i++) {
        pixelBuffer[i].setPixel(pixelBuffer[i].getR() * (r/100.0),
                                pixelBuffer[i].getG() * (g/100.0),
                                pixelBuffer[i].getB() * (b/100.0),
                                pixelBuffer[i].getA());
    }
}
