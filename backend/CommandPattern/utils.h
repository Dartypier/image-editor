#ifndef IMAGE_EDITOR_UTILS_H
#define IMAGE_EDITOR_UTILS_H

#include <vector>
#include "../Pixel.h"
#include "../Image.h"

void applyKernel(double kernel[3][3], Image& image, std::vector<Pixel>& pixelBuffer);

#endif
