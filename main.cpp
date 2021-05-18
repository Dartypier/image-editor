#include "Image.h"
#include "CommandPattern/Commands.h"

#define PATH QStringLiteral("../image-test/") //foler path
#define IMAGE QStringLiteral("test.jpg") //filename
#define OUT QStringLiteral("out.jpg") //output file

using namespace std;

int main() {

    Image test( PATH + IMAGE);
    CommandManager commandManager;

    std::shared_ptr<ICommand> c1(new flipXCommand(test));
    std::shared_ptr<ICommand> c2(new edgeDetectCommand(test));

    commandManager.execute(c1);
    commandManager.execute(c2);
    commandManager.undo();
    commandManager.redo();

    test.save(PATH + OUT);

    return 0;
}
