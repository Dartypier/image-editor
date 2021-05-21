#include "flipYCommand.h"

flipYCommand::flipYCommand(Image &image) : image(image) {
    bakData = image.getDeepData();
}

flipYCommand::~flipYCommand() {
    delete bakData;
}

void flipYCommand::execute() {
    image.flipY();
}

void flipYCommand::undo() {
    image.setDeepData(bakData);
}

void flipYCommand::redo() {
    execute();
}
