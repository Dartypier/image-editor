#include "gtest/gtest.h"
#include "../Image.h"
#include "../CommandPattern/Commands.h"

#define PATH QStringLiteral("../../../backend/test/test-images/")

class TestCommands : public ::testing::Test{

protected:
    Image not_uni;

    TestCommands(): not_uni(PATH + "not_uni.png"){}
};

TEST_F(TestCommands, BlurCommand){

     Pixel validated_not_uni[2*3] = {
             Pixel(180, 138, 75, 255), Pixel(146, 108, 102, 255), Pixel(112, 78, 129, 255),
             Pixel(174, 108, 138, 255), Pixel(130, 120, 153, 255), Pixel(86, 132, 168, 255)
     };

     blurCommand blurC(not_uni);
     blurC.execute();
     std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, BrightnessCommand){

    Pixel validated_not_uni[2 * 3] = {
            Pixel(255, 255, 147, 255), Pixel(255, 127, 127, 255), Pixel(214, 169, 255, 255),
            Pixel(255, 221, 255, 255), Pixel(152, 188, 255, 255), Pixel(215, 255, 255, 255)
    };

    brightnessCommand brightnessC(not_uni, 50);
    brightnessC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, BrightnessCommandOutOfRangeNegative) {

    Pixel validated_not_uni[2 * 3] = {
            Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255),
            Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255)
    };

    brightnessCommand brightnessC(not_uni, -120);
    brightnessC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, BrightnessCommandOutOfRangePositive) {

    Pixel validated_not_uni[2 * 3] = {
            Pixel(255, 255, 255, 255), Pixel(255, 254, 254, 255), Pixel(255, 255, 255, 255),
            Pixel(255, 255, 255, 255), Pixel(255, 255, 255, 255), Pixel(255, 255, 255, 255)
    };

    brightnessCommand brightnessC(not_uni, 120);
    brightnessC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, ColorMaskCommand) {

    Pixel validated_not_uni[2*3] ={
            Pixel(32, 25, 6, 255), Pixel(51, 0, 0, 255), Pixel(17, 4, 42, 255),
            Pixel(48, 9, 62, 255), Pixel(5, 6, 59, 255), Pixel(17, 25, 65, 255)
    };

    ASSERT_EQ(not_uni.getSize(), 6);

    colorMaskCommand colorMaskC(not_uni, 20, 10, 30);
    colorMaskC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    for(int i=0; i<6;i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, ColorMaskCommandOutOfRange) {

    Pixel validated_not_uni[2*3] ={
            Pixel(0, 25, 26, 255), Pixel(0, 0, 0, 255), Pixel(0, 4, 185, 255),
            Pixel(0, 9, 255, 255), Pixel(0, 6, 255, 255), Pixel(0, 25, 255, 255)
    };

    ASSERT_EQ(not_uni.getSize(), 6);

    colorMaskCommand colorMaskC(not_uni, -20, 10, 130);
    colorMaskC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    for(int i=0; i<6;i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, ContrastCommand) {

    //#1
    Pixel validated_not_uni[2 * 3] = {
            Pixel(177, 255, 0, 255), Pixel(255, 0, 0, 255), Pixel(66, 0, 150, 255),
            Pixel(255, 77, 246, 255), Pixel(0, 27, 231, 255), Pixel(68, 255, 255, 255)
    };

    contrastCommand contrastC(not_uni, 20);
    contrastC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, ContrastCommandOutOFRangePositive) {
    //#2
    Pixel validated_not_uni[2 * 3] = {
            Pixel(255, 255, 0, 255), Pixel(255, 0, 0, 255), Pixel(0, 0, 255, 255),
            Pixel(255, 0, 255, 255), Pixel(0, 0, 255, 255), Pixel(0, 255, 255, 255)
    };

    contrastCommand contrastC(not_uni, 120);
    contrastC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, ContrastCommandOutOfRangeNegative) {
    //#3
    Pixel validated_not_uni[2 * 3] = {
            Pixel(128, 128, 128, 255), Pixel(128, 127, 127, 255), Pixel(128, 128, 128, 255),
            Pixel(128, 128, 128, 255), Pixel(128, 128, 128, 255), Pixel(128, 128, 128, 255)
    };

    contrastCommand contrastC(not_uni, -120);
    contrastC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, EdgeDetectCommand) {

    Pixel validated_not_unit[2 * 3] = {
            Pixel(0, 0, 0, 255), Pixel(176, 176, 176, 255), Pixel(154, 154, 154, 255),
            Pixel(14, 14, 14, 255), Pixel(214, 214, 214, 255), Pixel(0, 0, 0, 255)
    };

    edgeDetectCommand edgeDetectC(not_uni);
    edgeDetectC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_unit[i]);
}

TEST_F(TestCommands, EmbossCommand) {

    Pixel validated_not_uni[2 * 3] = {
            Pixel(65, 0, 255, 255), Pixel(0, 0, 255, 255), Pixel(0, 255, 255, 255),
            Pixel(0, 0, 255, 255), Pixel(0, 255, 255, 255), Pixel(0, 255, 255, 255)
    };

    embossCommand embossC(not_uni);
    embossC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, FlipXCommand) {

    //not_uni.png data flipped X
    Pixel validated_not_uni[2 * 3] = {
            Pixel(87, 42, 143, 255), Pixel(255, 0, 0, 255), Pixel(161, 255, 20, 255),
            Pixel(88, 255, 218, 255),Pixel(25, 61, 197, 255), Pixel(243, 94, 207, 255)};

    flipXCommand flipXC(not_uni);
    flipXC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, FlipYCommand) {

    //not_uni.png
    Pixel validated_not_uni[2 * 3] = {
            Pixel(243, 94, 207, 255), Pixel(25, 61, 197, 255), Pixel(88, 255, 218, 255),
            Pixel(161, 255, 20, 255), Pixel(255, 0, 0, 255), Pixel(87, 42, 143, 255)};

    flipYCommand flipYC(not_uni);
    flipYC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, grayScale){

    Pixel validated_not_uni[2*3] = {
            Pixel(217, 217, 217, 255), Pixel(54, 54, 54, 255), Pixel(58, 58, 58, 255),
            Pixel(133, 133, 133, 255), Pixel(63, 63, 63, 255), Pixel(216, 216, 216, 255)
    };

    grayScaleCommand grayScaleC(not_uni);
    grayScaleC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, RotateClockwiseCommand) {
    Pixel validated_not_uni[3 * 2] = {
            Pixel(243, 94, 207, 255), Pixel(161, 255, 20, 255),
            Pixel(25, 61, 197, 255), Pixel(255, 0, 0, 255),
            Pixel(88, 255, 218, 255), Pixel(87, 42, 143, 255)};

    rotateClockwiseCommand rotateClockwiseC(not_uni);
    rotateClockwiseC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, RotateAntiClockwiseCommand) {

    Pixel validated_not_uni[3 * 2] = {
            Pixel(87, 42, 143, 255), Pixel(88, 255, 218, 255),
            Pixel(255, 0, 0, 255), Pixel(25, 61, 197, 255),
            Pixel(161, 255, 20, 255), Pixel(243, 94, 207, 255)};

    rotateAntiClockwiseCommand rotateAntiClockwiseC(not_uni);
    rotateAntiClockwiseC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, ScaleDownCommand) {

    Pixel validated_not_uni[1 * 2] = {
            Pixel(161, 255, 20, 255), Pixel(255, 0, 0, 255)
    };

    scaleCommand scaleC(not_uni, 2, 1);
    scaleC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2);
    for (int i = 0; i < 2; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, ScaleUpCommand) {

    Pixel validated_not_uni[2 * 4] = {
            Pixel(161, 255, 20, 255), Pixel(161, 255, 20, 255), Pixel(255, 0, 0, 255), Pixel(87, 42, 143, 255),
            Pixel(243, 94, 207, 255), Pixel(243, 94, 207, 255), Pixel(25, 61, 197, 255), Pixel(88, 255, 218, 255)
    };

    scaleCommand scaleC(not_uni, 4, 2);
    scaleC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 8);
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(TestCommands, SharpenCommand) {

    Pixel validated_not_uni[2 * 3] = {
            Pixel(0, 255, 0, 255), Pixel(255, 0, 0, 255), Pixel(0, 0, 225, 255),
            Pixel(255, 0, 255, 255), Pixel(0, 0, 255, 255), Pixel(49, 255, 255, 255)
    };

    sharpenCommand sharpenC(not_uni);
    sharpenC.execute();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}