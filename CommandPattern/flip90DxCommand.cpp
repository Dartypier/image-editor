#include "flip90DxCommand.h"

flip90DxCommand::flip90DxCommand(Image &image) : image(image){
    bakData = image.getDeepData();
}

flip90DxCommand::~flip90DxCommand() {
    delete bakData;
}

void flip90DxCommand::execute() {
    image.flip90Dx();
}

void flip90DxCommand::undo() {
    image.setDeepData(bakData);
}

void flip90DxCommand::redo() {
    execute();
}
