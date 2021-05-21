#ifndef IMAGE_EDITOR_IMAGE_H
#define IMAGE_EDITOR_IMAGE_H

//handles RGBA/RGB images
#include <QImage>
#include <QString>
#include "Pixel.h"

using namespace std;

class Image {

    friend class grayScaleOptimizedCommand;
    friend class colorMaskCommand;
    friend class flipXCommand;
    friend class flipYCommand;
    friend class flip90SxCommand;
    friend class flip90DxCommand;
    friend class contrastCommand;
    friend class brightnessCommand;
    friend class scaleCommand;
    friend class blurCommand;
    friend class sharpenCommand;
    friend class edgeDetectCommand;
    friend class embossCommand;

private:
    QImage backData; //stores backend data infos
    QString path;
    QString filename;
    int w;
    int h;
    Pixel* data;
    size_t size;

    void createData();
    void pureFilename();

    void setDeepData(Pixel* bakData);

    void applyKernel(double[3][3]); //used by kernel processing methods

public:
    explicit Image(const QString& path);
    ~Image(); //delete dynamic data matrix
    void save(const QString& outPath, int quality = -1); //-1 auto compression //0-100 quality range
    Image(Image& image) = delete;

    string getPath() const;
    string getFilename() const;
    Pixel* getDeepData() const;
    size_t getSize() const;

    void grayScaleOptimized(); //color optimized (not gray scale average algorithm)
    void colorMask(int r, int g, int b); //values from 0-100
    void flipX();
    void flipY();
    void flip90Dx();
    void flip90Sx();
    void contrast(int contrast); //allowed -100 - 100
    void brightness(int value); //allowed -100 - 100
    void scale(int percentual);
    void scale(int x, int y);

    //kernel processing uses EXTEND method for edge pixels
    void blur();
    void sharpen();
    void edgeDetect();
    void emboss();
    //void original(); test purpose



};


#endif
