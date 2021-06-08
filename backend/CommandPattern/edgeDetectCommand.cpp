#include "edgeDetectCommand.h"
#include "utils.h"
#include "grayScaleCommand.h"

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

    grayScaleCommand grayScaleC(image);
    grayScaleC.execute();
    applyKernel(edgeDetectKer, image, pixelBuffer);

}
