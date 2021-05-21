#include "utils.h"

int truncate0_255(int value) {
    if (value < 0)
        return 0;
    if (value > 255)
        return 255;
    else
        return value;
}

int truncate_m100_100(int value) {
    if (value < -100)
        return -100;
    if (value > 100)
        return 100;
    else
        return value;
}

int truncate0_100(int value) {
    if (value < 0)
        return 0;
    if (value > 100)
        return 100;
    else
        return value;
}