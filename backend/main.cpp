#include "../frontend/MainWindow.h"
#include "QApplication"
#include "Image.h"
#include "CommandPattern/Commands.h"
#include <iostream>

#define PATH QStringLiteral("/home/jacopo/CLionProjects/image_editor/image-test/") //folder path
#define IMAGE QStringLiteral("test.jpg") //filename
#define OUT QStringLiteral("out.jpg") //output file

using namespace std::chrono;

int main(int argc, char *argv[]) {

//    Image test(PATH + IMAGE);
//    CommandManager commandManager;

//    std::shared_ptr<ICommand> c1(new embossCommand(test));

//    commandManager.execute(c1);

//    test.save(PATH + OUT);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
