#include "gtest/gtest.h"
#include "../Pixel.h"

class TestPixel: public ::testing::Test{

protected:
    Pixel solid;
    Pixel alpha;
    Pixel out;

    TestPixel():
        solid(78, 200, 15, 255),
        alpha(78, 200, 15, 100),
        out(-20, 90, 255, 258)
        {}
};

TEST_F(TestPixel,  Ctor){

    Pixel pix = Pixel(10, 30, 50, 255);
    Pixel pix1 = Pixel(300, 20, -163, -1);

    ASSERT_EQ(pix.getR(), 10);
    ASSERT_EQ(pix.getG(), 30);
    ASSERT_EQ(pix.getB(), 50);
    ASSERT_EQ(pix.getA(), 255);

    EXPECT_EQ(pix1.getR(), 44);
    EXPECT_EQ(pix1.getG(), 20);
    EXPECT_EQ(pix1.getB(), 93);
    EXPECT_EQ(pix1.getA(), 255);
}

TEST_F(TestPixel, NoParamCtor){

    Pixel pix = Pixel();
    EXPECT_EQ(pix.getR(), 0);
    EXPECT_EQ(pix.getG(), 0);
    EXPECT_EQ(pix.getB(), 0);
    EXPECT_EQ(pix.getA(), 0);
}

TEST_F(TestPixel, CPYCtor){

    Pixel pix = Pixel(solid);
    EXPECT_EQ(pix, solid);
    pix = Pixel(alpha);
    EXPECT_EQ(pix, alpha);
}

TEST_F(TestPixel, Equal){

    Pixel pix = Pixel(alpha);
    EXPECT_FALSE(solid==alpha);
    EXPECT_TRUE(pix==alpha);
}

TEST_F(TestPixel, NotEqual){

    Pixel pix = Pixel(alpha);
    EXPECT_TRUE(solid!=alpha);
    EXPECT_FALSE(pix!=alpha);
}

TEST_F(TestPixel, GETR){
    ASSERT_EQ(solid.getR(), 78);
    EXPECT_EQ(out.getR(), 236);
}

TEST_F(TestPixel, GETG){
    ASSERT_EQ(solid.getG(), 200);
    EXPECT_EQ(out.getG(), 90);
}

TEST_F(TestPixel, GETB){
    ASSERT_EQ(solid.getB(), 15);
    EXPECT_EQ(out.getB(), 255);
}

TEST_F(TestPixel, GETA){
    ASSERT_EQ(solid.getA(), 255);
    EXPECT_EQ(out.getA(), 2);
}

TEST_F(TestPixel, ToQColor){
    QColor color_solid = Pixel::toQColor(solid);
    QColor color_alpha = Pixel::toQColor(alpha);

    int r;
    int g;
    int b;
    int a;

    color_solid.getRgb(&r, &g, &b, &a);

    ASSERT_EQ(solid.getR(), r);
    ASSERT_EQ(solid.getG(), g);
    ASSERT_EQ(solid.getB(), b);
    ASSERT_EQ(solid.getA(), a);

    color_alpha.getRgb(&r, &g, &b, &a);

    EXPECT_EQ(alpha.getR(), r);
    EXPECT_EQ(alpha.getG(), g);
    EXPECT_EQ(alpha.getB(), b);
    EXPECT_EQ(alpha.getA(), a);
}

TEST_F(TestPixel, FromQColor){

    QColor color_alpha = QColor(1, 20, 255, 60);
    Pixel pix = Pixel::fromQColor(color_alpha);

    ASSERT_EQ(pix.getR(), 1) <<+pix.getR();
    ASSERT_EQ(pix.getG(), 20) << +pix.getG();
    ASSERT_EQ(pix.getB(), 255) << +pix.getB();
    ASSERT_EQ(pix.getA(), 60)<<+pix.getA();

    //cannot check out_of_range values because if ctor parametrs of QColor are invalid
    //an invalid object(not usable) is created
}