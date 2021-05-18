#ifndef IMAGE_EDITOR_PIXEL_H
#define IMAGE_EDITOR_PIXEL_H

#include <cstdint>
#include <QColor>

//frontend for QColor

class Pixel {

private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

public:
    Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Pixel(); //all black
    Pixel(const Pixel& pixel);

    //Pixel operator=(const Pixel& pixel);

    uint8_t getR() const;
    uint8_t getG() const;
    uint8_t getB() const;
    uint8_t getA() const;

    static QColor toQColor(const Pixel&);
    static Pixel fromQColor(const QColor&);
};


#endif //IMAGE_EDITOR_PIXEL_H
