#include "Pixel.h"
#include "utils.h"

Pixel::Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) :
        r(r), g(g), b(b), a(a) {}

Pixel::Pixel() : Pixel(0, 0, 0, 255) {}

uint8_t Pixel::getR() const { return r; }

uint8_t Pixel::getG() const { return g; }

uint8_t Pixel::getB() const { return b; }

uint8_t Pixel::getA() const { return a; }

QColor Pixel::toQColor(const Pixel &oldc) {
    QColor newc(oldc.getR(), oldc.getG(), oldc.getB(), oldc.getA());
    return newc;
}

Pixel Pixel::fromQColor(const QColor &oldc) {
    int rc;
    int gc;
    int bc;
    int ac;

    oldc.getRgb(&rc, &gc, &bc, &ac);

    return Pixel(rc, gc, bc, ac);
}

Pixel::Pixel(const Pixel &color) {
    this->r = color.getR();
    this->g = color.getG();
    this->b = color.getB();
    this->a = color.getA();
}

bool Pixel::operator==(const Pixel &pixel) const {

    if (getR() == pixel.getR() &&
        getG() == pixel.getG() &&
        getB() == pixel.getB() &&
        getA() == pixel.getA())
        return true;
    else
        return false;
}

bool Pixel::operator!=(const Pixel &pixel) const {
    return !operator==(pixel);
}

void Pixel::setPixel(int r, int g, int b, int a) {

    this->r = truncate0_255(r);
    this->g = truncate0_255(g);
    this->b = truncate0_255(b);
    this->a = truncate0_255(a);
}
