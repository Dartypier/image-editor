#define PATH QStringLiteral("../../test/test-images/")

#include "gtest/gtest.h"
#include "../Image.h"
#include "../utils.h"

class ImageTest : public ::testing::Test {

protected:
    Image solid_pink;
    Image solid_green;
    Image alpha_yellow;
    Image big;
    Image not_uni;
    Image mono_green;

    ImageTest() :
            solid_pink(PATH + "3x2_solid_pink.jpg"),
            solid_green(PATH + "3x3_solid_green.jpg"),
            alpha_yellow(PATH + "3x4_alpha_yellow.png"),
            big(PATH + "big.jpg"),
            not_uni(PATH + "not_uni.png"),
            mono_green(PATH + "mono_green.png") {}

};

TEST_F(ImageTest, Ctor) {
    ASSERT_EQ(solid_pink.getSize(), 6);
    Pixel *data = solid_pink.getDeepData();

    Pixel tempData[6] = {
            Pixel(255, 10, 227, 255), Pixel(255, 10, 227, 255), Pixel(255, 10, 227, 255),
            Pixel(255, 10, 227, 255), Pixel(255, 10, 227, 255), Pixel(255, 10, 227, 255)
    };

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(data[i], tempData[i]);
}

TEST_F(ImageTest, Path) {
    EXPECT_EQ(solid_pink.getPath(), "../../test/test-images/3x2_solid_pink.jpg");
    EXPECT_EQ(solid_green.getPath(), "../../test/test-images/3x3_solid_green.jpg");
    EXPECT_EQ(alpha_yellow.getPath(), "../../test/test-images/3x4_alpha_yellow.png");
}

TEST_F(ImageTest, Filename) {

    EXPECT_EQ(solid_pink.getFilename(), "3x2_solid_pink.jpg");
    EXPECT_EQ(solid_green.getFilename(), "3x3_solid_green.jpg");
    EXPECT_EQ(alpha_yellow.getFilename(), "3x4_alpha_yellow.png");
}

TEST_F(ImageTest, Size) {
    EXPECT_EQ(solid_pink.getSize(), 6);
    EXPECT_EQ(solid_green.getSize(), 9);
    EXPECT_EQ(alpha_yellow.getSize(), 12);
    EXPECT_EQ(big.getSize(), 2560 * 1440);
}

void calculateCheckGrayScale(Image &img) {
    Pixel *tempData;
    Pixel *data;

    //test img
    tempData = img.getDeepData();
    img.grayScaleOptimized();
    data = img.getDeepData();

    for (int i = 0; i < img.getSize(); i++) {
        int gray = 0.2126 * tempData[i].getR() + 0.7125 * tempData[i].getG() + 0.0722 * tempData[i].getB();
        tempData[i] = Pixel(gray, gray, gray, tempData[i].getA());

        ASSERT_EQ(data[i], tempData[i]);
    }

    delete tempData;
    delete data;
}

TEST_F(ImageTest, GrayScale) {

    calculateCheckGrayScale(solid_pink);
    calculateCheckGrayScale(alpha_yellow);
}

TEST_F(ImageTest, ColorMask) {

    Pixel tempData[2*3] ={
            Pixel(32, 25, 6, 255), Pixel(51, 0, 0, 255), Pixel(17, 4, 42, 255),
            Pixel(48, 9, 62, 255), Pixel(5, 6, 59, 255), Pixel(17, 25, 65, 255)
    };

    ASSERT_EQ(not_uni.getSize(), 6);

    not_uni.colorMask(20, 10, 30);
    Pixel* data = not_uni.getDeepData();

    for(int i=0; i<6;i++)
        EXPECT_EQ(data[i], tempData[i]);
}

TEST_F(ImageTest, ColorMaskOutOfRange) {

    Pixel tempData[2*3] ={
            Pixel(0, 25, 20, 255), Pixel(0, 0, 0, 255), Pixel(0, 4, 143, 255),
            Pixel(0, 9, 207, 255), Pixel(0, 6, 197, 255), Pixel(0, 25, 218, 255)
    };

    ASSERT_EQ(not_uni.getSize(), 6);

    not_uni.colorMask(-20, 10, 130);
    Pixel* data = not_uni.getDeepData();

    for(int i=0; i<6;i++)
        EXPECT_EQ(data[i], tempData[i]);
}

TEST_F(ImageTest, FlipX) {

    //not_uni.png data flipped X
    Pixel tempData_not_uni[3 * 2] = {
            Pixel(161, 255, 20, 255), Pixel(243, 94, 207, 255),
            Pixel(255, 0, 0, 255), Pixel(25, 61, 197, 255),
            Pixel(87, 42, 143, 255), Pixel(88, 255, 218, 255)};

    Pixel tempData_mono_green[1] = {Pixel(66, 133, 7, 255)};

    not_uni.flip90Dx();
    not_uni.flipX();
    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(data[i], tempData_not_uni[i]);

    ASSERT_EQ(mono_green.getSize(), 1);

    delete data;
    data = mono_green.getDeepData();

    EXPECT_EQ(data[0], tempData_mono_green[0]);

    delete data;

}

TEST_F(ImageTest, FlipY) {

    //not_uni.png
    Pixel tempData_not_uni[2 * 3] = {
            Pixel(243, 94, 207, 255), Pixel(25, 61, 197, 255), Pixel(88, 255, 218, 255),
            Pixel(161, 255, 20, 255), Pixel(255, 0, 0, 255), Pixel(87, 42, 143, 255)};

    Pixel tempData_mono_green[1] = {Pixel(66, 133, 7, 255)};

    not_uni.flipY();
    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(data[i], tempData_not_uni[i]);

    delete data;
    data = mono_green.getDeepData();
    ASSERT_EQ(not_uni.getSize(), 6);

    EXPECT_EQ(data[0], tempData_mono_green[0]);

}

TEST_F(ImageTest, Flip90DX) {
    Pixel tempData_not_uni[3 * 2] = {
            Pixel(243, 94, 207, 255), Pixel(161, 255, 20, 255),
            Pixel(25, 61, 197, 255), Pixel(255, 0, 0, 255),
            Pixel(88, 255, 218, 255), Pixel(87, 42, 143, 255)};

    Pixel tempData_mono_green[1] = {Pixel(66, 133, 7, 255)};

    not_uni.flip90Dx();
    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(data[i], tempData_not_uni[i]);

    delete data;
    data = mono_green.getDeepData();
    ASSERT_EQ(mono_green.getSize(), 1);

    EXPECT_EQ(data[0], tempData_mono_green[0]);

    delete data;
}

TEST_F(ImageTest, Flip90SX) {

    Pixel tempData_not_uni[3 * 2] = {
            Pixel(87, 42, 143, 255), Pixel(88, 255, 218, 255),
            Pixel(255, 0, 0, 255), Pixel(25, 61, 197, 255),
            Pixel(161, 255, 20, 255), Pixel(243, 94, 207, 255)};

    Pixel tempData_mono_green[1] = {Pixel(66, 133, 7, 255)};

    not_uni.flip90Sx();
    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(data[i], tempData_not_uni[i]);

    delete data;
    data = mono_green.getDeepData();
    ASSERT_EQ(mono_green.getSize(), 1);

    EXPECT_EQ(data[0], tempData_mono_green[0]);

    delete data;
}

TEST_F(ImageTest, Contrast) {

    //#1
    Pixel tempData_not_uni_1[2 * 3] = {
            Pixel(177, 255, 0, 255), Pixel(255, 0, 0, 255), Pixel(66, 0, 150, 255),
            Pixel(255, 77, 246, 255), Pixel(0, 27, 231, 255), Pixel(68, 255, 255, 255)
    };

    not_uni.contrast(20);

    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(tempData_not_uni_1[i], data[i]);

    delete data;
}

TEST_F(ImageTest, ContrastOutOFRangePositive) {
    //#2
    Pixel tempData_not_uni_2[2 * 3] = {
            Pixel(255, 255, 0, 255), Pixel(255, 0, 0, 255), Pixel(0, 0, 255, 255),
            Pixel(255, 0, 255, 255), Pixel(0, 0, 255, 255), Pixel(0, 255, 255, 255)
    };

    not_uni.contrast(120);

    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(tempData_not_uni_2[i], data[i]);

    delete data;
}

TEST_F(ImageTest, ContrastOutOfRangeNegative) {
    //#3
    Pixel tempData_not_uni_3[2 * 3] = {
            Pixel(128, 128, 128, 255), Pixel(128, 127, 127, 255), Pixel(128, 128, 128, 255),
            Pixel(128, 128, 128, 255), Pixel(128, 128, 128, 255), Pixel(128, 128, 128, 255)
    };

    not_uni.contrast(-120);

    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);

    for (int i = 0; i < 6; i++)
        EXPECT_EQ(tempData_not_uni_3[i], data[i]);
}

TEST_F(ImageTest, Brightness) {

    Pixel tempData[2 * 3] = {
            Pixel(255, 255, 147, 255), Pixel(255, 127, 127, 255), Pixel(214, 169, 255, 255),
            Pixel(255, 221, 255, 255), Pixel(152, 188, 255, 255), Pixel(215, 255, 255, 255)
    };

    not_uni.brightness(50);
    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(data[i], tempData[i]);
}

TEST_F(ImageTest, BrightnessOutOfRangePositive) {

    Pixel tempData[2 * 3] = {
            Pixel(255, 255, 255, 255), Pixel(255, 254, 254, 255), Pixel(255, 255, 255, 255),
            Pixel(255, 255, 255, 255), Pixel(255, 255, 255, 255), Pixel(255, 255, 255, 255)
    };

    not_uni.brightness(120);
    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(data[i], tempData[i]);
}

TEST_F(ImageTest, BrightnessOutOfRangeNegative) {

    Pixel tempData[2 * 3] = {
            Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255),
            Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255), Pixel(0, 0, 0, 255)
    };

    not_uni.brightness(-120);
    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 6);
    for (int i = 0; i < 6; i++)
        EXPECT_EQ(data[i], tempData[i]);
}

TEST_F(ImageTest, ScaleParametersDown) {

    Pixel tempData[1 * 2] = {
            Pixel(161, 255, 20, 255), Pixel(255, 0, 0, 255)
    };

    not_uni.scale(2, 1);
    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 2);
    for (int i = 0; i < 2; i++)
        EXPECT_EQ(data[i], tempData[i]);
}

TEST_F(ImageTest, ScaleParametersUp) {

    Pixel tempData[2 * 4] = {
            Pixel(161, 255, 20, 255), Pixel(161, 255, 20, 255), Pixel(255, 0, 0, 255), Pixel(87, 42, 143, 255),
            Pixel(243, 94, 207, 255), Pixel(243, 94, 207, 255), Pixel(25, 61, 197, 255), Pixel(88, 255, 218, 255)
    };

    not_uni.scale(4, 2);
    Pixel *data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 8);
    for (int i = 0; i < 8; i++)
        EXPECT_EQ(data[i], tempData[i]);
}

TEST_F(ImageTest, Blur) {

    Pixel tempData_not_unit[2 * 3] = {
            Pixel(180, 138, 101, 255), Pixel(146, 108, 102, 255), Pixel(112, 78, 129, 255),
            Pixel(174, 108, 138, 255), Pixel(130, 120, 153, 255), Pixel(86, 132, 168, 255)
    };
    Pixel tempData_mono_green[1] = {Pixel(63, 126, 28, 255)};

    Pixel *data;

    not_uni.blur();
    data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(data[i], tempData_not_unit[i]);

    delete data;

    mono_green.blur();
    data = mono_green.getDeepData();

    ASSERT_EQ(mono_green.getSize(), 1);

    EXPECT_EQ(data[0], tempData_mono_green[0]);

    delete data;
}

TEST_F(ImageTest, EdgeDetect) {

    Pixel tempData_not_unit[2 * 3] = {
            Pixel(0, 0, 0, 255), Pixel(176, 176, 176, 255), Pixel(154, 154, 154, 255),
            Pixel(14, 14, 14, 255), Pixel(214, 214, 214, 255), Pixel(0, 0, 0, 255)
    };
    Pixel tempData_mono_green[1] = {Pixel(0, 0, 0, 255)};

    Pixel *data;

    not_uni.edgeDetect();
    data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(data[i], tempData_not_unit[i]);

    delete data;

    mono_green.edgeDetect();
    data = mono_green.getDeepData();

    ASSERT_EQ(mono_green.getSize(), 1);

    EXPECT_EQ(data[0], tempData_mono_green[0]);

    delete data;
}

TEST_F(ImageTest, Sharpen) {

    Pixel tempData_not_unit[2 * 3] = {
            Pixel(0, 255, 0, 255), Pixel(255, 0, 0, 255), Pixel(0, 0, 225, 255),
            Pixel(255, 0, 255, 255), Pixel(0, 0, 255, 255), Pixel(49, 255, 255, 255)
    };
    Pixel tempData_mono_green[1] = {Pixel(66, 133, 0, 255)};

    Pixel *data;

    not_uni.sharpen();
    data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(data[i], tempData_not_unit[i]);

    delete data;

    mono_green.sharpen();
    data = mono_green.getDeepData();

    ASSERT_EQ(mono_green.getSize(), 1);

    EXPECT_EQ(data[0], tempData_mono_green[0]);

    delete data;
}

TEST_F(ImageTest, Emboss) {

    Pixel tempData_not_unit[2 * 3] = {
            Pixel(65, 0, 71, 255), Pixel(0, 0, 255, 255), Pixel(0, 255, 255, 255),
            Pixel(0, 0, 255, 255), Pixel(0, 255, 255, 255), Pixel(0, 255, 255, 255)
    };
    Pixel tempData_mono_green[1] = {Pixel(66, 133, 0, 255)};

    Pixel *data;

    not_uni.emboss();
    data = not_uni.getDeepData();

    ASSERT_EQ(not_uni.getSize(), 2 * 3);

    for (int i = 0; i < (2 * 3); i++)
        EXPECT_EQ(data[i], tempData_not_unit[i]);

    delete data;

    mono_green.emboss();
    data = mono_green.getDeepData();

    ASSERT_EQ(mono_green.getSize(), 1);

    EXPECT_EQ(data[0], tempData_mono_green[0]);

    delete data;
}