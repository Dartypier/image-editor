#include "Image.h"
#include "CommandPattern/Commands.h"

#define PATH QStringLiteral("../test/test-images/") //foler path
#define IMAGE QStringLiteral("not_uni.png") //filename
#define OUT QStringLiteral("out.png") //output file

using namespace std;

int main() {

    Image test(PATH + IMAGE);
    CommandManager commandManager;

    std::shared_ptr<ICommand> c1(new grayScaleCommand(test));

    commandManager.execute(c1);

    test.save(PATH + OUT);

    return 0;
}
