#pragma once

#include <iostream>
#include <vector>
#include "Pixel.h"

using namespace std;

class Compressor
{
public:
	Compressor();
	Compressor(char * dataArray, int n_);
	~Compressor();

	void init(char * dataArray, int n_);
	bool encode();					// Creates compressed file from the pixelMatrix.
	bool decode(char * filename);	// Creates .png file from compressed file.

private:
	vector<Pixel> pixelMatrix;		// Matrix containing n*n Pixels.
	int n;							// Pixels per side in matrix.
	Pixel getPixel(int x, int y);	// Method to treat pixelMatrix as a matrix (kind of implementing pointer's algebra).
};

