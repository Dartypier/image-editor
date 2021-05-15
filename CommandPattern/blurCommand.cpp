#include "blurCommand.h"

blurCommand::blurCommand(Image &image) : image(image){
    bakData = image.getDeepData();
}

blurCommand::~blurCommand() {
    delete bakData;
}

void blurCommand::execute() {
    image.blur();
}

void blurCommand::undo() {
    image.setDeepData(bakData);
}

void blurCommand::redo() {
    execute();
}
