#include "borderColorPicker.h"
#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;
borderColorPicker::borderColorPicker(unsigned int borderSize, HSLAPixel fillColor, PNG &img, double tolerance)
{
    this->borderSize = borderSize;
    this->fillColor = fillColor;
    this->img = img;
    this->tolerance = tolerance;
}

HSLAPixel borderColorPicker::operator()(point p)
{
    HSLAPixel center = p.c.color;
    unsigned int width = img.width();
    unsigned int height = img.height();

    bool left = p.x < borderSize;
    bool top = p.y < borderSize;
    bool right = (unsigned int)abs((int)(p.x - width)) <= borderSize;
    bool bottom = (unsigned int)abs((int)(p.y - height)) <= borderSize;

    if (left || top || right || bottom) {
        return fillColor;
    }
    int euclidean = pow(borderSize, 2);
    for (unsigned int x = p.x - borderSize; x <= (p.x +borderSize); x++) {
        for (unsigned int y = p.y - borderSize; y <= (p.y + borderSize); y++) {
            if ((pow(x - p.x, 2) + pow(y - p.y, 2)) <= euclidean) {
                if (img.getPixel(x, y)->dist(center) > tolerance) {
                    return fillColor;
                }
            }
        }
    }
    return *(img.getPixel(p.x, p.y));
}
