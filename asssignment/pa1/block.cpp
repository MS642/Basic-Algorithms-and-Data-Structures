#include "block.h"
#include <cmath>

// set values in data attribute, based on a dimension x dimension square region
//   with upper-left corner at (left, upper) in the input PNG image
// The orientation of the pixels in the data vector must match the orientation
//   of the pixels in the PNG.
// PRE: upper and left (and upper + dimension, left + dimension) are valid
//        vector indices
void Block::Build(PNG& im, int upper, int left, int dimension) 
{
	data = vector<vector<HSLAPixel>>(dimension);
	for (int x = 0; x < dimension; x++) {
		data[x] = vector<HSLAPixel>(dimension);
		for (int y = 0; y < dimension; y++) {
			data[x][y] = *im.getPixel(left+x, upper+y);
		}
	}
}

// write the pixel colour data fom data attribute into im,
//   with upper-left corner at (left, upper)
// PRE: upper and left (and upper + dimension, left + dimension) are valid
//        vector indices
void Block::Render(PNG& im, int upper, int left) const
{
	for (unsigned int x = 0; x < data.size(); x++) {
		for (unsigned int y = 0; y < data.size(); y++) {
			 *im.getPixel(left + x, upper + y) = data[x][y];
		}
	}
}

// "Reverse" the Hue and Luminance channels for each pixel in the data attribute
//   to simulate a photo-negative effect.
// Refer to the HSLAPixel documentation to determine an appropriate transformation
//   for "reversing" hue and luminance.
void Block::Negative() 
{
	for (unsigned int x = 0; x < data.size(); x++) {
		for (unsigned int y = 0; y < data.size(); y++) {
			data[x][y].h = fmod((180.0 + data[x][y].h), 360.0);
			data[x][y].l = 1 - data[x][y].l;
		}
	}
}

// Return the horizontal (or vertical) size of the data block's image region
int  Block::Dimension() const
{
	return data.size();
}