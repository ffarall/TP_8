#pragma once
class Pixel
{
public:
	Pixel();
	Pixel(const char * R_, const char * G_,const char * B_,const char * Alpha_);

	unsigned char getR(void);
	unsigned char getG(void);
	unsigned char getB(void);
	unsigned char getAlpha(void);
	
	void operator= (Pixel& source);

	~Pixel();

private:
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char alpha;

};

