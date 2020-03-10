#include "fadeColorPicker.h"
#include <math.h>
#include "cs221util/PNG.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    fadeFactor = fade;
}
/**
     * Picks the color for pixel (x, y), which is a member of point p.
     * The new color consists of components h, s, and l.
     * The hue h, and saturation s, are unchanged by
     * the function, but the luminance decays as the
     * distance from the current point to the center,
     * increases.
     *
     *  The new luminance is simply newL = centerL * (fadeFactor)^(distSq).
     *  centerL, and all the information you need to compute distSq is
     * given via the input parameter p.
     *
     * @param p   The point for which you're picking a color
     * @return    The color chosen for (p).
     */
     /**
      * fadeColorPicker: a functor that determines the color that should be used
      * given a point containing both an n x and a y coordinate, and the
      * coordinates and color of the center to which (x,y) has been assigned.
      * The hue and saturation of the color of (x,y)
      * is the same as the center, but the luminiance is computed as
      * newL = (oldL * fadeFactor ^ (distSq)), where oldL is the center's
      * luminance, fadeFactor is a parameter, and distSq is the squared
      * Euclidean distance between the current point and the center.
      *
      */
HSLAPixel fadeColorPicker::operator()(point p)
{
    HSLAPixel newColor;
    HSLAPixel center = p.c.color;
    newColor.h = center.h;
    newColor.s = center.s;
    int x = (p.c.x - p.x);
    int y = (p.c.y - p.y);
    double dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
    dist = sqrt(dist);
    newColor.l = center.l * pow(fadeFactor, dist);
    return newColor;
}
