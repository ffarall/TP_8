#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Pixel.h"

using namespace std;

class Compressor
{
public:
	Compressor();
	Compressor(char * dataArray, double threshold_);
	~Compressor();

	void init(char * dataArray, int n_);
	bool encode(const char * filename);						// Creates compressed file from the pixelMatrix. Returns false when the encoding couldn’t be done
	bool decode(const char * filename);	// Creates .png file from compressed file.

private:
	Pixel getPixel(int x, int y);	// Method to treat pixelMatrix as a matrix (kind of implementing pointer's algebra).
	bool setPixel(Pixel& pixel_, unsigned int x, unsigned int y);
	bool decodeRec(fstream& fp, int x, int y, int ancho);
	bool encodeRec(int x, int y, int n_);

	vector<Pixel> pixelMatrix;		// Matrix containing n*n Pixels.
	unsigned int n;					// Pixels per side in matrix. For this implementation, since the number of pixels must be a power of 2, and the image must be squared, n can only be 1, 2, 4, 16, 64, 256...
	double threshold;				// Determines how much the original image is respected, where threshold=0 means image stays the same (with less compression) and threshold=100 means more compression at the cost of image quality.
	ofstream compressedFile;
};

