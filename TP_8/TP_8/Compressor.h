#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "Pixel.h"
#include "Error.h"

using namespace std;

class Compressor
{
public:
	Compressor();
	Compressor(char * dataArray, double threshold_);
	~Compressor();

	void init(char * dataArray, int n_);
	bool encode();					// Creates compressed file from the pixelMatrix.
	bool decode(const char * filename);	// Creates .png file from compressed file.
	
	bool isOk(void); // true if everything is ok, false si hay error
	string getError(void);

private:
	Pixel getPixel(int x, int y);	// Method to treat pixelMatrix as a matrix (kind of implementing pointer's algebra).
	bool setPixel(Pixel& pixel_, unsigned int x, unsigned int y);
	bool decodeRec(fstream& fp, int x, int y, int ancho);

	vector<Pixel> pixelMatrix;		// Matrix containing n*n Pixels.
	unsigned int n;					// Pixels per side in matrix.
	double threshold;
	Error compressorError;
};

