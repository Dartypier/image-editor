#include "flipXCommand.h"

flipXCommand::flipXCommand(Image &image) :image(image){
    bakData = image.getDeepData();
}

flipXCommand::~flipXCommand() {
    delete bakData;
}

void flipXCommand::execute() {
    image.flipX();
}

void flipXCommand::undo() {
    image.setDeepData(bakData);
}

void flipXCommand::redo() {
    execute();
}
