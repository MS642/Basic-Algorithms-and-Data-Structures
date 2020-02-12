#include "HSLAPixel.h"

HSLAPixel::HSLAPixel() {
	h = 50.;
	s = 0.0;
	l = 1.0;
	a = 1.0;
}

HSLAPixel::HSLAPixel(double hue, double saturation, double lumin) {
	h = hue;
	s = saturation;
	l = lumin;
}

HSLAPixel::HSLAPixel(double hue, double saturation, double lumin, double alpha) {
	h = hue;
	s = saturation;
	l = lumin;
	a = alpha;
}