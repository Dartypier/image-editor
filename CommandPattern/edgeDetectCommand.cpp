#include "edgeDetectCommand.h"
#include "utils.h"

edgeDetectCommand::edgeDetectCommand(Image &image) : image(image), pixelBuffer(image.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

void edgeDetectCommand::execute() {
    edgeDetect();
}

void edgeDetectCommand::undo() {
    pixelBuffer = backupPixelBuffer;
}

void edgeDetectCommand::redo() {
    execute();
}

void edgeDetectCommand::edgeDetect() {

    double edgeDetectKer[3][3] = {{0, 1,  0},
                                  {1, -4, 1},
                                  {0, 1,  0}};

    //grayScaleOptimized();
    applyKernel(edgeDetectKer, image, pixelBuffer);
}
