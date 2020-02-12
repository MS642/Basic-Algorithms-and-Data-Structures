#pragma once
class HSLAPixel {
public:
	HSLAPixel();
	HSLAPixel(double hue, double saturation, double lumin);
	HSLAPixel(double hue, double saturation, double lumin, double alpha);
	double h;
	double s;
	double l;
	double a;

};