#include "brightnessCommand.h"
#include "../utils.h"

brightnessCommand::brightnessCommand(Image &image, int value) : image(image), value(value), pixelBuffer(image.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

void brightnessCommand::execute() {
    brightness();
}

void brightnessCommand::undo() {
    pixelBuffer = backupPixelBuffer;
}

void brightnessCommand::redo() {
    execute();
}

void brightnessCommand::brightness(){
    double normalizedValue = truncate_m100_100(value) * 2.55;

    for (int i = 0; i < image.getSize(); i++) {
        pixelBuffer[i].setPixel(pixelBuffer[i].getR() + normalizedValue,
                                pixelBuffer[i].getG() + normalizedValue,
                                pixelBuffer[i].getB() + normalizedValue,
                                pixelBuffer[i].getA());
    }
}