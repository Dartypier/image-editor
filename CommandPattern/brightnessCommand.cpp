#include "brightnessCommand.h"

brightnessCommand::brightnessCommand(Image &image, int value) : image(image), value(value) {
    bakData = image.getDeepData();
}

brightnessCommand::~brightnessCommand() {
    delete bakData;
}

void brightnessCommand::execute() {
    image.brightness(value);
}

void brightnessCommand::undo() {
    image.setDeepData(bakData);
}

void brightnessCommand::redo() {
    execute();
}
