#include "Color.h"
#include "utils.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a):
    r(r), g(g), b(b), a(a){}

Color::Color() : Color(0, 0, 0, 0){}

uint8_t Color::getR() const {return r;}
uint8_t Color::getG() const {return g;}
uint8_t Color::getB() const {return b;}
uint8_t Color::getA() const {return a;}

QColor Color::toQColor(Color oldc) {
    QColor newc(oldc.getR(), oldc.getG(), oldc.getB(), oldc.getA());
    return newc;
}

Color Color::fromQColor(const QColor& oldc) {
    int rc;
    int gc;
    int bc;
    int ac;

    oldc.getRgb(&rc, &gc, &bc, &ac);

    if(is0_255(rc) && is0_255(gc) && is0_255(bc) && is0_255(ac))
        return Color(rc, gc, bc, ac);
    else
        return Color();
}

Color::Color(const Color &color) {
    this->r = color.getR();
    this->g = color.getG();
    this->b = color.getB();
    this->a = color.getA();
}
