#include "flipYCommand.h"

flipYCommand::flipYCommand(Image &image) : image(image), pixelBuffer(image.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

void flipYCommand::execute() {
    flipY();
}

void flipYCommand::undo() {
    backupPixelBuffer = pixelBuffer;
}

void flipYCommand::redo() {
    execute();
}

void flipYCommand::flipY() {

    Pixel temp;

    if (image.getH() > 2)
        for (int x = 0; x < image.getW(); x++)
            for (int y = 0; y < image.getH() / 2; y++) {
                temp = pixelBuffer[x + y * image.getW()];
                pixelBuffer[x + y * image.getW()] = pixelBuffer[x + (image.getH() - 1 - y) * image.getW()];
                pixelBuffer[x + (image.getH() - 1 - y) * image.getW()] = temp;
            }
    else if (image.getH() == 2) {
        for (int x = 0; x < image.getW(); x++) {
            temp = pixelBuffer[(1 * image.getW() + x)];
            pixelBuffer[1 * image.getW() + x] = pixelBuffer[0 * image.getW() + x];
            pixelBuffer[0 * image.getW() + x] = temp;
        }
    }
}
