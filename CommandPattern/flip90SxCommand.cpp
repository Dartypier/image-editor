#include "flip90SxCommand.h"

flip90SxCommand::flip90SxCommand(Image &image) :image(image){
    bakData = image.getDeepData();
}

flip90SxCommand::~flip90SxCommand() {
    delete bakData;
}

void flip90SxCommand::execute() {
    image.flip90Sx();
}

void flip90SxCommand::undo() {
    image.setDeepData(bakData);
}

void flip90SxCommand::redo() {
    execute();
}
