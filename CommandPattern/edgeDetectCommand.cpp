#include "edgeDetectCommand.h"

edgeDetectCommand::edgeDetectCommand(Image &image):image(image) {
    bakData = image.getDeepData();
}

edgeDetectCommand::~edgeDetectCommand() {
    delete bakData;
}

void edgeDetectCommand::execute() {
    image.sharpen();
}

void edgeDetectCommand::undo() {
    image.setDeepData(bakData);
}

void edgeDetectCommand::redo() {
    execute();
}
