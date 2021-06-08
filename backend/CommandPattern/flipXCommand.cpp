#include "flipXCommand.h"

flipXCommand::flipXCommand(Image &image) : image(image), pixelBuffer(image.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

void flipXCommand::execute() {
    flipX();
}

void flipXCommand::undo() {
    pixelBuffer = backupPixelBuffer;
}

void flipXCommand::redo() {
    execute();
}

void flipXCommand::flipX() {
    Pixel temp;

    if (image.getW() > 2)
        for (int y = 0; y < image.getH(); y++)
            for (int x = 0; x < image.getW() / 2; x++) {
                temp = pixelBuffer[x + y * image.getW()];
                pixelBuffer[x + y * image.getW()] = pixelBuffer[(image.getW() - 1 - x) + y * image.getW()];
                pixelBuffer[(image.getW() - 1 - x) + y * image.getW()] = temp;
            }
    else if (image.getW() == 2) {
        for (int y = 0; y < image.getH(); y++) {
            temp = pixelBuffer[y * image.getW() + 1];
            pixelBuffer[y * image.getW() + 1] = pixelBuffer[y * image.getW() + 0];
            pixelBuffer[y * image.getW() + 0] = temp;
        }
    }

}
