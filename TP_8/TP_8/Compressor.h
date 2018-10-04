#pragma once

#include <iostream>
#include <vector>
#include "Pixel.h"

using namespace std;

class Compressor
{
public:
	Compressor();
	Compressor(char * dataArray);
	~Compressor();

private:
	vector<Pixel> pixelMatrix;		// Matrix containing n*n Pixels.
	int n;							// Pixels per side in matrix.
};

