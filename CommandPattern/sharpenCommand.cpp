#include "sharpenCommand.h"

sharpenCommand::sharpenCommand(Image &image) : image(image) {
    bakData = image.getDeepData();
}

sharpenCommand::~sharpenCommand() {
    delete bakData;
}

void sharpenCommand::execute() {
    image.sharpen();
}

void sharpenCommand::undo() {
    image.setDeepData(bakData);
}

void sharpenCommand::redo() {
    execute();
}
