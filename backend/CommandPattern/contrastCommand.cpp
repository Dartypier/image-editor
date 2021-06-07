#include "contrastCommand.h"
#include "../utils.h"

contrastCommand::contrastCommand(Image &image, int contrastValue) : image(image), contrastValue(contrastValue), pixelBuffer(image.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

void contrastCommand::execute() {
    contrast();
}

void contrastCommand::undo() {
    pixelBuffer = backupPixelBuffer;
}

void contrastCommand::redo() {
    execute();
}

void contrastCommand::contrast() {

    double normalizedContrast = truncate_m100_100(contrastValue) * 2.55;
    double factor = (259.0 * (normalizedContrast + 255)) / (255.0 * (259 - normalizedContrast));

    for (int i = 0; i < image.getSize(); i++) {
        pixelBuffer[i].setPixel(factor * (pixelBuffer[i].getR() - 128) + 128,
                                factor * (pixelBuffer[i].getG() - 128) + 128,
                                factor * (pixelBuffer[i].getB() - 128) + 128,
                                pixelBuffer[i].getA());
    }

}
