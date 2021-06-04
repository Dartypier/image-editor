#include "utils.h"

void applyKernel(double kernel[3][3], Image& image, std::vector<Pixel>& pixelBuffer) {
    int sumR;
    int sumG;
    int sumB;

    int h = image.getH();
    int w = image.getW();

    std::vector<Pixel> tempPixelBuffer;
    tempPixelBuffer.reserve((h+2)*(w+2));
    tempPixelBuffer.resize((h+2)*(w+2));

    //not very elegant

    //borders are extended to prevent frame creation on processed images

    //copy inside matrix
    for (int i = 1; i < h + 1; i++) {
        for (int j = 1; j < w + 1; j++) {
            tempPixelBuffer[i * (w + 2) + j] = pixelBuffer[(i-1) * w + (j-1)];

//                    Pixel(data[(i - 1) * w + (j - 1)].getR(), data[(i - 1) * w + (j - 1)].getG(),
//                                          data[(i - 1) * w + (j - 1)].getB(), 0);
        }
    }

    for (int i = 1; i < w + 1; i++) //upper (not round)
        tempPixelBuffer[0 * (w + 2) + i] = pixelBuffer[(h - 1) * w + (i - 1)];

//                Pixel(data[0 * w + (i - 1)].getR(), data[0 * w + (i - 1)].getG(),
//                                      data[0 * w + (i - 1)].getB(), 0);

    for (int i = 1; i < w + 1; i++) //below
        tempPixelBuffer[(h + 1) * (w + 2) + i] = pixelBuffer[(h - 1) * w + (i - 1)];

//                Pixel(data[(h - 1) * w + (i - 1)].getR(), data[(h - 1) * w + (i - 1)].getG(),
//                                            data[(h - 1) * w + (i - 1)].getB(), 0);

    for (int i = 1; i < h + 1; i++) //sx
        tempPixelBuffer[i * (w + 2) + 0] = pixelBuffer[(i - 1) * w + (w - 1)];

//                Pixel(data[(i - 1) * w + 0].getR(), data[(i - 1) * w + 0].getG(),
//                                      data[(i - 1) * w + 0].getB(), 0);

    for (int i = 1; i < h + 1; i++) //dx
        tempPixelBuffer[i * (w + 2) + (w + 1)] = pixelBuffer[(i - 1) * w + (w - 1)];

//                Pixel(data[(i - 1) * w + (w - 1)].getR(), data[(i - 1) * w + (w - 1)].getG(),
//                                            data[(i - 1) * w + (w - 1)].getB(), 0);

    //sx round top
    tempPixelBuffer[0 * (w + 2) + 0] = pixelBuffer[0 * w + 0];

//            Pixel(data[0 * w + 0].getR(), data[0 * w + 0].getG(), data[0 * w + 0].getA(), 0);

    //dx round top
    tempPixelBuffer[0 * (w + 2) + (w + 1)] = pixelBuffer[0 * w + (w - 1)];

//            Pixel(data[0 * w + (w - 1)].getR(), data[0 * w + (w - 1)].getG(),
//                                        data[0 * w + (w - 1)].getB(), 0);

    //sx round below
    tempPixelBuffer[(h + 1) * (w + 2) + 0] = pixelBuffer[(h - 1) * w + 0];

//            Pixel(data[(h - 1) * w + 0].getR(), data[(h - 1) * w + 0].getG(),
//                                        data[(h - 1) * w + 0].getB(), 0);

    //dx round below
    tempPixelBuffer[(h + 1) * (w + 2) + (w + 1)] = pixelBuffer[(h - 1) * w + (w - 1)];

//            Pixel(data[(h - 1) * w + (w - 1)].getR(), data[(h - 1) * w + (w - 1)].getG(),
//                                              data[(h - 1) * w + (w - 1)].getB(), 0);


    for (int i = 1; i < h + 1; i++) {
        for (int j = 1; j < w + 1; j++) {
            sumR = 0;
            sumG = 0;
            sumB = 0;

            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    sumR +=
                            tempPixelBuffer[(i + k - 1) * (w + 2) + (j + l - 1)].getR() * kernel[k][l];

                    sumG +=
                            tempPixelBuffer[(i + k - 1) * (w + 2) + (j + l - 1)].getG() * kernel[k][l];

                    sumB +=
                            tempPixelBuffer[(i + k - 1) * (w + 2) + (j + l - 1)].getB() * kernel[k][l];
                }
            }

            //assign to pixelBuffer
            pixelBuffer[(i - 1) * w + (j - 1)].setPixel(sumR, sumG, sumB, pixelBuffer[(i - 1) * w + (j - 1)].getA());

//                    Pixel(truncate0_255(sumR), truncate0_255(sumG), truncate0_255(sumB),
//                                                data[(i - 1) * w + (j - 1)].getA());
        }
    }
}