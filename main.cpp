#include "Image.h"
#include "CommandPattern/Commands.h"

#define PATH QStringLiteral("../image-test/") //test purpose
#define IMAGE QStringLiteral("foscal.png")
#define OUT QStringLiteral("out.png")

using namespace std;

int main() {

    Image test( PATH + IMAGE);
    CommandManager commandManager;

    std::shared_ptr<ICommand> c1(new flipXCommand(test));
    std::shared_ptr<ICommand> c2(new grayScaleOptimizedCommand(test));

    commandManager.execute(c1);
    commandManager.execute(c2);
    commandManager.undo();
    commandManager.undo();
    commandManager.redo();
    //commandManager.redo();

    test.save(PATH + OUT);

    return 0;
}
