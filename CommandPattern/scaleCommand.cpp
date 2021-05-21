#include "scaleCommand.h"

scaleCommand::scaleCommand(Image &image, int percentual) : image(image), percentual(percentual) {
    bakData = image.getDeepData();
}

scaleCommand::scaleCommand(Image &image, int x, int y) : image(image), x(x), y(y) {
    bakData = image.getDeepData();
}

scaleCommand::~scaleCommand() {
    delete bakData;
}

void scaleCommand::execute() {
        image.scale(x, y);
}

void scaleCommand::undo() {
    image.setDeepData(bakData);
}

void scaleCommand::redo() {
    execute();
}
