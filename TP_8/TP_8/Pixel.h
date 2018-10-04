#pragma once
class Pixel
{
public:
	Pixel();
	Pixel(const char * content);

	unsigned char getR(void);
	unsigned char getG(void);
	unsigned char getB(void);
	unsigned char getAlpha(void);
	
	~Pixel();

private:
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char alpha;

};

