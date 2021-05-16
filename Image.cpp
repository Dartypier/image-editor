#include "Image.h"
#include "utils.h"
#include <QColor>
#include "Pixel.h"
#include <iostream>
#include <algorithm>
#include <cmath>

Image::Image(const QString& path): backData(path), path(path){
    //TODO: add exception
    backData = backData.convertToFormat(QImage::Format_ARGB32); //only 32bit depth supported(auto conversion)
    w = backData.width();                                        //it's a 24bit (8*3) + alpha channel (8bit)
    h = backData.height();
    size = w*h;
    data = new Pixel [size];
    createData();
}

void Image::calculateFilename(){ //better name has to be defined
    filename = path.mid(path.lastIndexOf("/"));
}

void Image::createData() {
    for(int y=0; y<h; y++) //rows
        for(int x=0; x<w; x++){ //columns
//            if(!backData.valid(x, y)) //TODO: add throw
//                cout << "NOT" << endl;
            Pixel currentPixel = Pixel::fromQColor(backData.pixelColor(x, y)); //get rgba values (because depth is 24 is 0-255 rgb+alpha)
                data[y*w+x] = currentPixel;

            //securing data (all default data is deleted now): [manual test]
            //backData.setPixelColor(x, y, qRgba(0, 0, 0, 0)); [passed]
        }
}

void Image::save(const QString& outPath, int quality){

    for(int y=0; y<h; y++) //rows
        for(int x=0; x<w; x++){ //columns
            backData.setPixelColor(x, y, Pixel::toQColor(data[y*w+x]));
        }

    //save image on disk
    backData.save(outPath, nullptr, quality);
}


Image::~Image() {
    delete data;
}

string Image::getPath() const{
    return path.toStdString();
}

string Image::getFilename() const{
    return filename.toStdString();
}

size_t Image::getSize() const{
    return size;

}

void Image::grayScaleOptimized() {

    for(int y=0; y<h; y++) //rows
        for(int x=0; x<w; x++){ //columns
            int gray = 0.2126*data[y*w+x].getR() + 0.7125*data[y*w+x].getG() + 0.0722*data[y*w+x].getB();
            Pixel grayPixelColor(gray, gray, gray, data[y*w+x].getA());
            data[y*w+x] = grayPixelColor;
        }
}

void Image::colorMask(int r, int g, int b) { //accepted from 0 to 100
    if(is0_100(r) && is0_100(g) && is0_100(b)){

        for(int i=0; i<size; i++) {
            data[i] = Pixel(data[i].getR()*(r/double(100)),
                        data[i].getG()*(g/double(100)),
                        data[i].getB()*(b/double(100)),
                        data[i].getA());
        }
    }
}

void Image::flipX(){
    Pixel temp;

    for(int y=0; y<h; y++)
        for(int x=0; x<w/2;x++){
            temp = data[x+y*w];
            data[x+y*w] = data[(w-1-x)+y*w];
            data[(w-1-x)+y*w] = temp;
        }
}

void Image::flipY() {
    Pixel temp;

    for(int x=0; x<w; x++)
        for(int y=0; y<h/2; y++){
            temp = data[x+y*w];
            data[x+y*w] = data[x+(h-1-y)*w];
            data[x+(h-1-y)*w] = temp;
        }
}

void Image::brightness(int value){
    double normalizedValue = truncate_m100_100(value) * 2.55;

    for(int i=0; i<size; i++){
        data[i] = Pixel(
                truncate0_255(data[i].getR() + normalizedValue),
                truncate0_255(data[i].getG() + normalizedValue),
                truncate0_255(data[i].getB() + normalizedValue),
                data[i].getA());
    }
}

void Image::contrast(int contrast) {

    double normalizedContrast = truncate_m100_100(contrast) * 2.55;
    double factor = (259.0*(normalizedContrast+255))/(255.0*(259-normalizedContrast));

    int cr;
    int cg;
    int cb;

    for(int i=0;i<size;i++){
        cr = truncate0_255(factor* (data[i].getR()-128) + 128);
        cg = truncate0_255(factor* (data[i].getG()-128) + 128);
        cb = truncate0_255(factor* (data[i].getB()-128) + 128);
        data[i] = Pixel(cr, cg, cb, data[i].getA());
    }
}

void Image::flip90Dx() {

    backData = QImage(h, w, QImage::Format_RGB32);
    //TODO: implement copy and custom iterator
    Pixel * tempArr = new Pixel[size];

    for(int i=0; i<size; i++) {
        tempArr[i] = data[i];
    }

    for(int i=0; i < w; i++)
        for(int j=0; j<h; j++)
            data[i*h+j] = tempArr[(h-j-1)*w+i];

    int temp = w;
    w = h;
    h = temp;

    delete[] tempArr;
}

void Image::flip90Sx() {
    backData = QImage(h, w, QImage::Format_RGB32);
    //TODO: implement copy and custom iterator
    //TODO: implement method
}

void Image::scale(int percentual) {

    //TODO: add limits
    int x = w + w*(percentual/100);
    int y = h + h*(percentual/100);

    scale(x, y);
}

void Image::scale(int x, int y) {
    Pixel *newData = new Pixel[x*y];

    double x_ratio = w/(double)x;
    double y_ratio = h/(double)y;
    double px, py;
    for(int i=0; i<y; i++)
        for(int j=0; j<x; j++)
        {
            px = floor(j*x_ratio);
            py = floor(i*y_ratio);
            newData[i*x+j] = data [(int)((py*w)+px)];
        }

    w = x;
    h = y;
    size = w*h;
    delete[] data;
    data = newData;
    QImage newImage(reinterpret_cast<const uchar *>(data), w, h, QImage::Format_RGB32);
    backData = newImage;
}

//3x3 kernels
void Image::applyKernel() {

}

void Image::blur() {
    int blurKer [3][3] = {{1, 1, 1},
                 {1, 1, 1},
                 {1, 1, 1}};


}

void Image::sharpen() {
    int sharpenKer [3][3] = {{0, -1, 0},
                             {-1, 5, -1},
                             {0, -1, 0}};
}

void Image::edgeDetect() {
    int edgeDetectKer [3][3] = {{0, 1, 0},
                                {1, -2, 1},
                                {0, 1, 0}};
}

void Image::emboss() {
    int embossKer [3][3] = {{-2, -1, 0},
                            {-1, 1, 1},
                            {0, 1, 2}};
}

Pixel *Image::getDeepData() const {
    Pixel* dataCopy = new Pixel[getSize()];

    for(int i=0; i<size; i++)
        dataCopy[i] = Pixel(data[i]); //call copy constructor for deep copy

    return dataCopy;
}

void Image::setDeepData(Pixel* bakData) {
    for(int i=0; i<getSize(); i++)
        data[i] = Pixel(bakData[i]);
}
