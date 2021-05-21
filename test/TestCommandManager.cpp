#include "gtest/gtest.h"
#include "../CommandPattern/CommandManager.h"
#include "../Image.h"
#include "../CommandPattern/Commands.h"

#define PATH QStringLiteral("../../test/test-images/")


class TestCommandManager: public ::testing::Test{

protected:
    Image img;
    CommandManager commandManager;

    TestCommandManager() :
        img(PATH + "not_uni.png"),
        commandManager()
    {}
};

TEST_F(TestCommandManager, Execute){

    Pixel flippedData[3*2] = {
            Pixel(243, 94, 207, 255), Pixel(25, 61, 197, 255), Pixel(88, 255, 218, 255),
            Pixel(161, 255, 20, 255),Pixel(255, 0, 0, 255), Pixel(87, 42, 143, 255) };

    std::shared_ptr<ICommand> c1(new flipYCommand(img));
    commandManager.execute(c1);

    Pixel* data = img.getDeepData();

    ASSERT_EQ(img.getSize(), 6);

    for(int i =0; i<img.getSize(); i++)
        EXPECT_EQ(data[i], flippedData[i]);
}

TEST_F(TestCommandManager, Undo){

    Pixel* originalData = img.getDeepData();

    std::shared_ptr<ICommand> c1(new flipYCommand(img));
    commandManager.execute(c1);
    commandManager.undo();

    Pixel* data = img.getDeepData();

    ASSERT_EQ(img.getSize(), 6);

    for(int i =0; i<img.getSize(); i++)
        EXPECT_EQ(data[i], originalData[i]);
}

TEST_F(TestCommandManager, Redo){

    Pixel flippedData[3*2] = {
            Pixel(243, 94, 207, 255), Pixel(25, 61, 197, 255), Pixel(88, 255, 218, 255),
            Pixel(161, 255, 20, 255),Pixel(255, 0, 0, 255), Pixel(87, 42, 143, 255) };

    std::shared_ptr<ICommand> c1(new flipYCommand(img));
    commandManager.execute(c1);

    Pixel* data = img.getDeepData();
    //undo command
    commandManager.undo();
    //redo command
    commandManager.redo();

    ASSERT_EQ(img.getSize(), 6);

    for(int i =0; i<img.getSize(); i++)
        EXPECT_EQ(data[i], flippedData[i]);
}