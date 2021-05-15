#include "contrastCommand.h"

contrastCommand::contrastCommand(Image &image, int conrast) : image(image), contrast(conrast) {
    bakData = image.getDeepData();
}

contrastCommand::~contrastCommand() {
    delete bakData;
}

void contrastCommand::execute() {
    image.contrast(contrast);
}

void contrastCommand::undo() {
    image.setDeepData(bakData);
}

void contrastCommand::redo() {
    execute();
}
