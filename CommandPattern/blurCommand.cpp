#include "blurCommand.h"
#include "utils.h"

blurCommand::blurCommand(Image &image) : image(image), pixelBuffer(image.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

void blurCommand::execute() {
    blur();
}

void blurCommand::undo() {
    pixelBuffer = backupPixelBuffer;
}

void blurCommand::redo() {
    execute();
}

void blurCommand::blur(){

    double blurKer[3][3] = {{1 / 9.0, 1 / 9.0, 1 / 9.0},
                            {1 / 9.0, 1 / 9.0, 1 / 9.0},
                            {1 / 9.0, 1 / 9.0, 1 / 9.0}};

    applyKernel(blurKer, image, pixelBuffer);
}
