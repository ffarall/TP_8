#include "Pixel.h"



Pixel::Pixel()
{
	R = G = B = alpha = 0;
}

Pixel::Pixel(const char * R_, const char * G_, const char * B_, const char * Alpha_)
{
	R = *R_;
	G = *G_;
	B = *B_;
	alpha = *Alpha_;
}

unsigned char Pixel::getR(void)
{
	return R;
}

unsigned char Pixel::getG(void)
{
	return G;
}

unsigned char Pixel::getB(void)
{
	return B;
}

unsigned char Pixel::getAlpha(void)
{
	return alpha;
}

void Pixel::operator=(Pixel & source)
{
	R = source.R;
	G = source.G;
	B = source.B;
	alpha = source.alpha;
}


Pixel::~Pixel()
{
}
