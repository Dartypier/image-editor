#ifndef IMAGE_EDITOR_COLOR_H
#define IMAGE_EDITOR_COLOR_H

#include <cstdint>
#include <QColor>

//frontend for QColor

class Color {

private:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

public:
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Color(); //all black
    Color(const Color& color);

    uint8_t getR() const;
    uint8_t getG() const;
    uint8_t getB() const;
    uint8_t getA() const;

    static QColor toQColor(Color);
    static Color fromQColor(const QColor&);
};


#endif //IMAGE_EDITOR_COLOR_H
