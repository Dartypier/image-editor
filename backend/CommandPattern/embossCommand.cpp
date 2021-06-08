#include "embossCommand.h"
#include "utils.h"

embossCommand::embossCommand(Image &image) : image(image), pixelBuffer(image.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

void embossCommand::execute() {
    emboss();
}

void embossCommand::undo() {
    pixelBuffer = backupPixelBuffer;
}

void embossCommand::redo() {
    execute();
}

void embossCommand::emboss() {

    double embossKer[3][3] = {{-2, -1, 0},
                              {-1, 1,  1},
                              {0,  1,  2}};

    applyKernel(embossKer, image, pixelBuffer);

}
