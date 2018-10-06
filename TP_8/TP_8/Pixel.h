#pragma once
class Pixel
{
public:
	Pixel();
	Pixel(const unsigned char R_, const unsigned char G_,const unsigned char B_,const unsigned char Alpha_);

	unsigned char getR(void);
	unsigned char getG(void);
	unsigned char getB(void);
	unsigned char getAlpha(void);
	void setR(unsigned char R_);
	void setG(unsigned char G_);
	void setB(unsigned char B_);
	void setAlpha(unsigned char alpha_);
	
	~Pixel();

private:
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char alpha;

};

