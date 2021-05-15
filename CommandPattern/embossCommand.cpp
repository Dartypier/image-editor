#include "embossCommand.h"

embossCommand::embossCommand(Image &image) : image(image) {
    bakData = image.getDeepData();
}

embossCommand::~embossCommand() {
    delete bakData;
}

void embossCommand::execute() {
    image.emboss();
}

void embossCommand::undo() {
    image.setDeepData(bakData);
}

void embossCommand::redo() {
    execute();
}
