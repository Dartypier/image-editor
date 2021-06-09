#include "rotateClockwiseCommand.h"

rotateClockwiseCommand::rotateClockwiseCommand(Image &image) : image(image), pixelBuffer(image.getPixelBuffer()){
    backupPixelBuffer = pixelBuffer;
}

void rotateClockwiseCommand::execute() {
    rotateClockwise();
}

void rotateClockwiseCommand::undo() {
    pixelBuffer = backupPixelBuffer;
    image.swapDimension();
}

void rotateClockwiseCommand::redo() {
    execute();
}

void rotateClockwiseCommand::rotateClockwise() {

    std::vector<Pixel> tempPixelBuffer = pixelBuffer;

    for (int i = 0; i < image.getW(); i++)
        for (int j = 0; j < image.getH(); j++)
            pixelBuffer[i * image.getH() + j] = tempPixelBuffer[(image.getH() - j - 1) * image.getW() + i];

    image.swapDimension();
}
