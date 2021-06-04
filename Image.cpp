#include "Image.h"
#include <QColor>
#include "Pixel.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include "QFileInfo"

using namespace std;

Image::Image(const QString &path) : rawImage(path), path(path) {
    //TODO: add exception
    rawImage = rawImage.convertToFormat(QImage::Format_ARGB32); //only 32bit depth supported(auto conversion)
    w = rawImage.width();                                        //it's a 24bit (8*3) + alpha channel (8bit)
    h = rawImage.height();

    pixelBuffer.reserve(getSize());
    initPixelBuffer();
    pureFilename();
}

void Image::pureFilename() {
    QFileInfo qFilename(path);
    filename = qFilename.fileName();
}

void Image::initPixelBuffer() {
    for (int y = 0; y < h; y++) //rows
        for (int x = 0; x < w; x++) { //columns
//            if(!backData.valid(x, y)) //TODO: add throw
//                cout << "NOT" << endl;
            pixelBuffer.emplace_back(Pixel::fromQColor(rawImage.pixelColor(x, y))); //get rgba values (because depth is 24 is 0-255 rgb+alpha)

            //securing data (all default data is deleted now): [manual test]
            //backData.setPixelColor(x, y, qRgba(0, 0, 0, 0)); [passed]
        }
}

void Image::save(const QString &outPath, int quality) {

    rawImage = QImage(w, h, QImage::Format_ARGB32);

    for (int y = 0; y < h; y++) //rows
        for (int x = 0; x < w; x++) { //columns
            rawImage.setPixelColor(x, y, Pixel::toQColor(pixelBuffer[y * w + x]));
        }

    //save image on disk
    rawImage.save(outPath, nullptr, quality);
}

string Image::getPath() const {
    return path.toStdString();
}

string Image::getFilename() const {
    return filename.toStdString();
}

size_t Image::getSize() const {
    return w * h;
}

int Image::getW() const{
    return w;
}

int Image::getH() const{
    return h;
}

void Image::setW(int w){
    this->w = w;
}

void Image::setH(int h){
    this->h = h;
}

//pass a reference (no copy, better performance)
std::vector<Pixel>& Image::getPixelBuffer() {

    return pixelBuffer;
}

void Image::swapDimension() {
    swap(h, w);
}