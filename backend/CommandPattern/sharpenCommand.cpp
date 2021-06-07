#include "sharpenCommand.h"
#include "utils.h"

sharpenCommand::sharpenCommand(Image &image) : image(image), pixelBuffer(image.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

void sharpenCommand::execute() {
    sharpen();
}

void sharpenCommand::undo() {
    pixelBuffer = backupPixelBuffer;
}

void sharpenCommand::redo() {
    execute();
}

void sharpenCommand::sharpen(){

    double sharpenKer[3][3] = {{-1, -1, -1},
                               {-1, 9,  -1},
                               {-1, -1, -1}};

    applyKernel(sharpenKer, image, pixelBuffer);

}
