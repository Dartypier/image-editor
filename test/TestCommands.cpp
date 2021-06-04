#define PATH QStringLiteral("../../test/test-images/")

#include "gtest/gtest.h"
#include "../Image.h"
#include "../CommandPattern/Commands.h"

class CommandsTest : public ::testing::Test{

protected:
    Image not_uni;

    CommandsTest(): not_uni(PATH + "not_uni.png"){}
};

TEST_F(CommandsTest, BlurCommand){

     Pixel validated_not_uni[2*3] = {
             Pixel(138, 120, 131, 255), Pixel(130, 120, 153, 255), Pixel(86, 108, 159, 255),
             Pixel(148, 102, 152, 255), Pixel(130, 120, 153, 255), Pixel(86, 132, 168, 255)
     };

     blurCommand blurC(not_uni);
     blurC.blur();
     std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, BrightnessCommand){

    Pixel validated_not_uni[2 * 3] = {
            Pixel(255, 255, 147, 255), Pixel(255, 127, 127, 255), Pixel(214, 169, 255, 255),
            Pixel(255, 221, 255, 255), Pixel(152, 188, 255, 255), Pixel(215, 255, 255, 255)
    };

    brightnessCommand brightnessC(not_uni, 50);
    brightnessC.brightness();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, BrightnessCommandOutOfRangeNegative) {

    Pixel validated_not_uni[2 * 3] = {
            Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255),
            Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255)
    };

    brightnessCommand brightnessC(not_uni, -120);
    brightnessC.brightness();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, BrightnessCommandOutOfRangePositive) {

    Pixel validated_not_uni[2 * 3] = {
            Pixel(255, 255, 255, 255), Pixel(255, 254, 254, 255), Pixel(255, 255, 255, 255),
            Pixel(255, 255, 255, 255), Pixel(255, 255, 255, 255), Pixel(255, 255, 255, 255)
    };

    brightnessCommand brightnessC(not_uni, 120);
    brightnessC.brightness();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, ColorMaskCommand) {

    Pixel validated_not_uni[2*3] ={
            Pixel(32, 25, 6, 255), Pixel(51, 0, 0, 255), Pixel(17, 4, 42, 255),
            Pixel(48, 9, 62, 255), Pixel(5, 6, 59, 255), Pixel(17, 25, 65, 255)
    };

    ASSERT_EQ(not_uni.getSize(), 6);

    colorMaskCommand colorMaskC(not_uni, 20, 10, 30);
    colorMaskC.colorMask();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    for(int i=0; i<6;i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, ColorMaskCommandOutOfRange) {

    Pixel validated_not_uni[2*3] ={
            Pixel(0, 25, 26, 255), Pixel(0, 0, 0, 255), Pixel(0, 4, 185, 255),
            Pixel(0, 9, 255, 255), Pixel(0, 6, 255, 255), Pixel(0, 25, 255, 255)
    };

    ASSERT_EQ(not_uni.getSize(), 6);

    colorMaskCommand colorMaskC(not_uni, -20, 10, 130);
    colorMaskC.colorMask();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    for(int i=0; i<6;i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, ContrastCommand) {

    //#1
    Pixel validated_not_uni[2 * 3] = {
            Pixel(177, 255, 0, 255), Pixel(255, 0, 0, 255), Pixel(66, 0, 150, 255),
            Pixel(255, 77, 246, 255), Pixel(0, 27, 231, 255), Pixel(68, 255, 255, 255)
    };

    contrastCommand contrastC(not_uni, 20);
    contrastC.contrast();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, ContrastCommandOutOFRangePositive) {
    //#2
    Pixel validated_not_uni[2 * 3] = {
            Pixel(255, 255, 0, 255), Pixel(255, 0, 0, 255), Pixel(0, 0, 255, 255),
            Pixel(255, 0, 255, 255), Pixel(0, 0, 255, 255), Pixel(0, 255, 255, 255)
    };

    contrastCommand contrastC(not_uni, 120);
    contrastC.contrast();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, ContrastCommandOutOfRangeNegative) {
    //#3
    Pixel validated_not_uni[2 * 3] = {
            Pixel(128, 128, 128, 255), Pixel(128, 127, 127, 255), Pixel(128, 128, 128, 255),
            Pixel(128, 128, 128, 255), Pixel(128, 128, 128, 255), Pixel(128, 128, 128, 255)
    };

    contrastCommand contrastC(not_uni, -120);
    contrastC.contrast();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, EdgeDetectCommand) {

    Pixel validated_not_unit[2 * 3] = {
            Pixel(184, 0, 255, 255), Pixel(0, 255, 255, 255), Pixel(170, 255, 7, 255),
            Pixel(0, 255, 0, 255), Pixel(255, 166, 0, 255), Pixel(0, 0, 0, 255)
    };

    edgeDetectCommand edgeDetectC(not_uni);
    edgeDetectC.edgeDetect();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_unit[i]);
}

TEST_F(CommandsTest, EmbossCommand) {

    Pixel validated_not_uni[2 * 3] = {
            Pixel(57, 0, 231, 255), Pixel(0, 109, 145, 255), Pixel(45, 255, 255, 255),
            Pixel(138, 0, 255, 255), Pixel(0, 255, 255, 255), Pixel(0, 255, 255, 255)
    };

    embossCommand embossC(not_uni);
    embossC.emboss();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, FlipXCommand) {

    //not_uni.png data flipped X
    Pixel validated_not_uni[2 * 3] = {
            Pixel(87, 42, 143, 255), Pixel(255, 0, 0, 255), Pixel(161, 255, 20, 255),
            Pixel(88, 255, 218, 255),Pixel(25, 61, 197, 255), Pixel(243, 94, 207, 255)};

    flipXCommand flipXC(not_uni);
    flipXC.flipX();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, FlipYCommand) {

    //not_uni.png
    Pixel validated_not_uni[2 * 3] = {
            Pixel(243, 94, 207, 255), Pixel(25, 61, 197, 255), Pixel(88, 255, 218, 255),
            Pixel(161, 255, 20, 255), Pixel(255, 0, 0, 255), Pixel(87, 42, 143, 255)};

    flipYCommand flipYC(not_uni);
    flipYC.flipY();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, grayScale){

    Pixel validated_not_uni[2*3] = {
            Pixel(217, 217, 217, 255), Pixel(54, 54, 54, 255), Pixel(58, 58, 58, 255),
            Pixel(133, 133, 133, 255), Pixel(63, 63, 63, 255), Pixel(216, 216, 216, 255)
    };

    grayScaleCommand grayScaleC(not_uni);
    grayScaleC.grayScale();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, RotateClockwiseCommand) {
    Pixel validated_not_uni[3 * 2] = {
            Pixel(243, 94, 207, 255), Pixel(161, 255, 20, 255),
            Pixel(25, 61, 197, 255), Pixel(255, 0, 0, 255),
            Pixel(88, 255, 218, 255), Pixel(87, 42, 143, 255)};

    rotateClockwiseCommand rotateClockwiseC(not_uni);
    rotateClockwiseC.rotateClockwise();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, RotateAntiClockwiseCommand) {

    Pixel validated_not_uni[3 * 2] = {
            Pixel(87, 42, 143, 255), Pixel(88, 255, 218, 255),
            Pixel(255, 0, 0, 255), Pixel(25, 61, 197, 255),
            Pixel(161, 255, 20, 255), Pixel(243, 94, 207, 255)};

    rotateAntiClockwiseCommand rotateAntiClockwiseC(not_uni);
    rotateAntiClockwiseC.rotateAnticlockwise();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, ScaleDownCommand) {

    Pixel validated_not_uni[1 * 2] = {
            Pixel(161, 255, 20, 255), Pixel(255, 0, 0, 255)
    };

    scaleCommand scaleC(not_uni, 2, 1);
    scaleC.scale();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2);
    for (int i = 0; i < 2; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, ScaleUpCommand) {

    Pixel validated_not_uni[2 * 4] = {
            Pixel(161, 255, 20, 255), Pixel(161, 255, 20, 255), Pixel(255, 0, 0, 255), Pixel(87, 42, 143, 255),
            Pixel(243, 94, 207, 255), Pixel(243, 94, 207, 255), Pixel(25, 61, 197, 255), Pixel(88, 255, 218, 255)
    };

    scaleCommand scaleC(not_uni, 4, 2);
    scaleC.scale();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 8);
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}

TEST_F(CommandsTest, SharpenCommand) {

    Pixel validated_not_uni[2 * 3] = {
            Pixel(255, 255, 0, 255), Pixel(255, 0, 0, 255), Pixel(40, 0, 0, 255),
            Pixel(255, 0, 255, 255), Pixel(0, 0, 255, 255), Pixel(49, 255, 255, 255)
    };

    sharpenCommand sharpenC(not_uni);
    sharpenC.sharpen();
    std::vector<Pixel> pixelBuffer = not_uni.getPixelBuffer();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(pixelBuffer[i], validated_not_uni[i]);
}