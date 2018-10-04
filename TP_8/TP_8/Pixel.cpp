#include "Pixel.h"



Pixel::Pixel()
{
	R = G = B = alpha = 0;
}

Pixel::Pixel(const char * content)
{
	R = *content;
	G = *(content+1);
	B = *(content+2);
	alpha = *(content+3);
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


Pixel::~Pixel()
{
}
