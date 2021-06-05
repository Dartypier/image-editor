#include "Image.h"
#include "CommandPattern/Commands.h"

#include "chrono"
#include <iostream>

#define PATH QStringLiteral("../image-test/") //foler path
#define IMAGE QStringLiteral("foscal.png") //filename
#define OUT QStringLiteral("out.png") //output file

using namespace std::chrono;

int main() {

    auto start = high_resolution_clock::now();

    Image test(PATH + IMAGE);
    CommandManager commandManager;

    std::shared_ptr<ICommand> c1(new grayScaleCommand(test));

    commandManager.execute(c1);

    test.save(PATH + OUT);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;

    return 0;
}
