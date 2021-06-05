#include "Image.h"
#include "CommandPattern/Commands.h"

#include "chrono"
#include <iostream>

#define PATH QStringLiteral("../image-test/") //foler path
#define IMAGE QStringLiteral("test.jpg") //filename
#define OUT QStringLiteral("out.jpg") //output file

using namespace std::chrono;

int main() {

    auto start = high_resolution_clock::now();

    Image test(PATH + IMAGE);
    CommandManager commandManager;

    std::shared_ptr<ICommand> c1(new sharpenCommand(test));

    commandManager.execute(c1);

    test.save(PATH + OUT);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << duration.count() << endl;

    return 0;
}
