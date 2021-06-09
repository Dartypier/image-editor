#include "scaleCommand.h"
#include <cmath>

scaleCommand::scaleCommand(Image &image, int x, int y) : image(image), x(x), y(y), pixelBuffer(image.getPixelBuffer()) {
    backupPixelBuffer = pixelBuffer;
}

void scaleCommand::execute() {
        scale();
}

void scaleCommand::undo() {
    pixelBuffer = backupPixelBuffer;
    image.setW(backupW);
    image.setH(backupH);
}

void scaleCommand::redo() {
    execute();
}

void scaleCommand::scale() {

    if (x < 1)
        x = 1;
    if (y < 1)
        y = 1;

    if(x>10000)
        x=10000;
    if(y>10000)
        y=10000;

    std::vector<Pixel> newPixelBuffer;
    newPixelBuffer.resize(y*x);

    double x_ratio = image.getW() / (double) x;
    double y_ratio = image.getH() / (double) y;
    double px;
    double py;

    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++) {
            px = floor(j * x_ratio);
            py = floor(i * y_ratio);
            newPixelBuffer[i * x + j] = pixelBuffer[(int) ((py * image.getW()) + px)];
        }

    backupW = image.getW();
    image.setW(x);

    backupH = image.getH();
    image.setH(y);

    pixelBuffer = newPixelBuffer;
}
