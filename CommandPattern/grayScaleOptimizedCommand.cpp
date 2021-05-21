#include "grayScaleOptimizedCommand.h"

grayScaleOptimizedCommand::grayScaleOptimizedCommand(Image &image) : image(image) {
    //bakData = new Pixel[image.getFileSize()];
    //memcpy(bakData, image.data, sizeof(Pixel)*image.getFileSize());
    bakData = image.getDeepData();
}

void grayScaleOptimizedCommand::execute() {
    image.grayScaleOptimized();
}

void grayScaleOptimizedCommand::undo() {
    image.setDeepData(bakData);
}

void grayScaleOptimizedCommand::redo() {
    execute();
}

grayScaleOptimizedCommand::~grayScaleOptimizedCommand() {
    delete bakData;
}
