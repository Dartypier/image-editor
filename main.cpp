#include "Image.h"
#include "CommandPattern/Commands.h"

#define PATH QStringLiteral("../image-test/") //test purpose
#define IMAGE QStringLiteral("test.jpg")
#define OUT QStringLiteral("out.jpg")

using namespace std;

int main() {

    Image test( PATH + IMAGE);
//    CommandManager commandManager;
//
//    std::shared_ptr<ICommand> c1(new flipXCommand(test));
//    std::shared_ptr<ICommand> c2(new grayScaleOptimizedCommand(test));
//
//    commandManager.execute(c1);
//    commandManager.execute(c2);
//    commandManager.undo();
//    commandManager.undo();
//    commandManager.redo();
//    //commandManager.redo();

    test.flip90Sx();
//    test.original();

    test.save(PATH + OUT);

    return 0;
}
