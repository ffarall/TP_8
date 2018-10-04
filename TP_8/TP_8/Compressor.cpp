#include "Compressor.h"
#include <cmath>



Compressor::Compressor() : pixelMatrix()
{
	n = 0;
}

Compressor::Compressor(char * dataArray, int n_) : pixelMatrix()
{
	init(dataArray, n_);
}


Compressor::~Compressor()
{
}

void Compressor::init(char * dataArray, int n_)
{
	n = n_;
	for (int i = 0; i < n * n; i++)
	{
		pixelMatrix.push_back(Pixel(*(dataArray + i + 1), *(dataArray + i + 2), *(dataArray + i + 3), *(dataArray + i + 4)));	// Add n*n Pixels initialised with (red, green, blue, alfa).
	}
}
