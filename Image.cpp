#include "Image.h"
#include "utils.h"
#include <QColor>
#include "Pixel.h"
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

Image::Image(const QString &path) : backData(path), path(path) {
    //TODO: add exception
    backData = backData.convertToFormat(QImage::Format_ARGB32); //only 32bit depth supported(auto conversion)
    w = backData.width();                                        //it's a 24bit (8*3) + alpha channel (8bit)
    h = backData.height();
    size = w * h;
    data = new Pixel[size];
    createData();
}

void Image::pureFilename() { //better name has to be defined
    filename = path.mid(path.lastIndexOf("/"));
}

void Image::createData() {
    for (int y = 0; y < h; y++) //rows
        for (int x = 0; x < w; x++) { //columns
//            if(!backData.valid(x, y)) //TODO: add throw
//                cout << "NOT" << endl;
            Pixel currentPixel = Pixel::fromQColor(
                    backData.pixelColor(x, y)); //get rgba values (because depth is 24 is 0-255 rgb+alpha)
            data[y * w + x] = currentPixel;

            //securing data (all default data is deleted now): [manual test]
            //backData.setPixelColor(x, y, qRgba(0, 0, 0, 0)); [passed]
        }
}

void Image::save(const QString &outPath, int quality) {

    for (int y = 0; y < h; y++) //rows
        for (int x = 0; x < w; x++) { //columns
            backData.setPixelColor(x, y, Pixel::toQColor(data[y * w + x]));
        }

    //save image on disk
    backData.save(outPath, nullptr, quality);
}


Image::~Image() {
    delete data;
}

string Image::getPath() const {
    return path.toStdString();
}

string Image::getFilename() const {
    return filename.toStdString();
}

size_t Image::getSize() const {
    return size;

}

void Image::grayScaleOptimized() {

    for (int y = 0; y < h; y++) //rows
        for (int x = 0; x < w; x++) { //columns
            int gray =
                    0.2126 * data[y * w + x].getR() + 0.7125 * data[y * w + x].getG() + 0.0722 * data[y * w + x].getB();

            Pixel grayPixelColor(gray, gray, gray, data[y * w + x].getA());
            data[y * w + x] = grayPixelColor;
        }
}

void Image::colorMask(int r, int g, int b) { //accepted from 0 to 100
    if (is0_100(r) && is0_100(g) && is0_100(b)) {

        for (int i = 0; i < size; i++) {
            data[i] = Pixel(data[i].getR() * (r / double(100)),
                            data[i].getG() * (g / double(100)),
                            data[i].getB() * (b / double(100)),
                            data[i].getA());
        }
    }
}

void Image::flipX() {
    Pixel temp;

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w / 2; x++) {
            temp = data[x + y * w];
            data[x + y * w] = data[(w - 1 - x) + y * w];
            data[(w - 1 - x) + y * w] = temp;
        }
}

void Image::flipY() {
    Pixel temp;

    for (int x = 0; x < w; x++)
        for (int y = 0; y < h / 2; y++) {
            temp = data[x + y * w];
            data[x + y * w] = data[x + (h - 1 - y) * w];
            data[x + (h - 1 - y) * w] = temp;
        }
}

void Image::brightness(int value) {
    double normalizedValue = truncate_m100_100(value) * 2.55;

    for (int i = 0; i < size; i++) {
        data[i] = Pixel(
                truncate0_255(data[i].getR() + normalizedValue),
                truncate0_255(data[i].getG() + normalizedValue),
                truncate0_255(data[i].getB() + normalizedValue),
                data[i].getA());
    }
}

void Image::contrast(int contrast) {

    double normalizedContrast = truncate_m100_100(contrast) * 2.55;
    double factor = (259.0 * (normalizedContrast + 255)) / (255.0 * (259 - normalizedContrast));

    for (int i = 0; i < size; i++) {
        int cr = truncate0_255(factor * (data[i].getR() - 128) + 128);
        int cg = truncate0_255(factor * (data[i].getG() - 128) + 128);
        int cb = truncate0_255(factor * (data[i].getB() - 128) + 128);
        data[i] = Pixel(cr, cg, cb, data[i].getA());
    }
}

void Image::flip90Dx() {

    backData = QImage(h, w, QImage::Format_RGB32);
    Pixel *tempArr = new Pixel[size];

    for (int i = 0; i < size; i++) {
        tempArr[i] = data[i];
    }

    for (int i = 0; i < w; i++)
        for (int j = 0; j < h; j++)
            data[i * h + j] = tempArr[(h - j - 1) * w + i];

    int temp = w;
    w = h;
    h = temp;

    delete[] tempArr;
}

void Image::flip90Sx() {
    backData = QImage(h, w, QImage::Format_RGB32);
    Pixel *tempArr = new Pixel[size];

    for (int i = 0; i < size; i++) {
        tempArr[i] = data[i];
    }

    for (int i = 0; i < w; i++) //row
        for (int j = 0; j < h; j++) //columns
            data[(w - i - 1) * h + j] = tempArr[j * w + i];

    int temp = w;
    w = h;
    h = temp;

    delete[] tempArr;
}

void Image::scale(int percentual) {

    //TODO: add limits
    int x = w + w * (percentual / 100);
    int y = h + h * (percentual / 100);

    scale(x, y);
}

void Image::scale(int x, int y) {
    Pixel *newData = new Pixel[x * y];

    double x_ratio = w / (double) x;
    double y_ratio = h / (double) y;
    double px;
    double py;

    for (int i = 0; i < y; i++)
        for (int j = 0; j < x; j++) {
            px = floor(j * x_ratio);
            py = floor(i * y_ratio);
            newData[i * x + j] = data[(int) ((py * w) + px)];
        }

    w = x;
    h = y;
    size = w * h;
    delete[] data;
    data = newData;
    QImage newImage(reinterpret_cast<const uchar *>(data), w, h, QImage::Format_RGB32);
    backData = newImage;
}

//3x3 kernels
void Image::applyKernel(double kernel[3][3]) {
    int sumR;
    int sumG;
    int sumB;

    Pixel *temp = new Pixel[(w + 2) * (h + 2)];

    //borders are extended to prevent frame creation on processed images

    //copy inside matrix
    for (int i = 1; i < h + 1; i++) {
        for (int j = 0; j < w + 1; j++) {
            temp[i * (w + 2) + j] = Pixel(data[(i - 1) * w + (j - 1)].getR(), data[(i - 1) * w + (j - 1)].getG(),
                                          data[(i - 1) * w + (j - 1)].getB(), 0);
        }
    }

    for (int i = 1; i < w + 1; i++) //upper (not round)
        temp[0 * (w + 2) + i] = Pixel(data[0 * w + (i - 1)].getR(), data[0 * w + (i - 1)].getG(),
                                      data[0 * w + (i - 1)].getB(), 0);

    for (int i = 1; i < w + 1; i++) //below
        temp[(h + 1) * (w + 2) + i] = Pixel(data[(h - 1) * w + (i - 1)].getR(), data[(h - 1) * w + (i - 1)].getG(),
                                            data[(h - 1) * w + (i - 1)].getB(), 0);

    for (int i = 1; i < h + 1; i++) //sx
        temp[i * (w + 2) + 0] = Pixel(data[(i - 1) * w + 0].getR(), data[(i - 1) * w + 0].getG(),
                                      data[(i - 1) * w + 0].getB(), 0);

    for (int i = 1; i < h + 1; i++) //dx
        temp[i * (w + 2) + (w + 1)] = Pixel(data[(i - 1) * w + (w - 1)].getR(), data[(i - 1) * w + (w - 1)].getG(),
                                            data[(i - 1) * w + (w - 1)].getB(), 0);

    //sx round top
    temp[0 * (w + 2) + 0] = Pixel(data[0 * w + 0].getR(), data[0 * w + 0].getG(), data[0 * w + 0].getA(), 0);

    //dx round top
    temp[0 * (w + 2) + (w + 1)] = Pixel(data[0 * w + (w - 1)].getR(), data[0 * w + (w - 1)].getG(),
                                        data[0 * w + (w - 1)].getB(), 0);

    //sx round below
    temp[(h + 1) * (w + 2) + 0] = Pixel(data[(h - 1) * w + 0].getR(), data[(h - 1) * w + 0].getG(),
                                        data[(h - 1) * w + 0].getB(), 0);

    //dx round below
    temp[(h + 1) * (w + 2) + (w + 1)] = Pixel(data[(h - 1) * w + (w - 1)].getR(), data[(h - 1) * w + (w - 1)].getG(),
                                              data[(h - 1) * w + (w - 1)].getB(), 0);


    for (int i = 1; i < h + 1; i++) {
        for (int j = 1; j < w + 1; j++) {
            sumR = 0;
            sumG = 0;
            sumB = 0;

            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    sumR +=
                            temp[(i + k - 1) * (w + 2) + (j + l - 1)].getR() * kernel[k][l];

                    sumG +=
                            temp[(i + k - 1) * (w + 2) + (j + l - 1)].getG() * kernel[k][l];

                    sumB +=
                            temp[(i + k - 1) * (w + 2) + (j + l - 1)].getB() * kernel[k][l];
                }
            }

            data[(i - 1) * w + (j - 1)] = Pixel(truncate0_255(sumR), truncate0_255(sumG), truncate0_255(sumB),
                                                data[(i - 1) * w + (j - 1)].getA());
        }
    }

    delete[] temp;
}

void Image::blur() {
    double blurKer[3][3] = {{1 / 9.0, 1 / 9.0, 1 / 9.0},
                            {1 / 9.0, 1 / 9.0, 1 / 9.0},
                            {1 / 9.0, 1 / 9.0, 1 / 9.0}};

    applyKernel(blurKer);

}

void Image::sharpen() {
    double sharpenKer[3][3] = {{-1,  -1, -1},
                               {-1, 9,  -1},
                               {-1,  -1, -1}};

    applyKernel(sharpenKer);
}

void Image::edgeDetect() {
    double edgeDetectKer[3][3] = {{0, 1, 0},
                                  {1, -4,  1},
                                  {0, 1, 0}};

    grayScaleOptimized();
    applyKernel(edgeDetectKer);
}

void Image::emboss() {
    double embossKer[3][3] = {{-2, -1, 0},
                              {-1, 1,  1},
                              {0,  1,  2}};

    applyKernel(embossKer);
}


//void Image::original() {
//    double identity[3][3] = {{0, 0, 0},
//                             {0, 1, 0},
//                             {0, 0, 0}};
//
//    applyKernel(identity);
//
//}

Pixel *Image::getDeepData() const {
    auto *dataCopy = new Pixel[getSize()];

    for (int i = 0; i < size; i++)
        dataCopy[i] = Pixel(data[i]); //call copy constructor for deep copy

    return dataCopy;
}

void Image::setDeepData(Pixel *bakData) {
    for (int i = 0; i < getSize(); i++)
        data[i] = Pixel(bakData[i]);
}