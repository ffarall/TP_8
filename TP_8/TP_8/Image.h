#pragma once
#include<iostream>


class ImageSize
{
public:
	ImageSize();
	ImageSize(int height, int width);
	int height;
	int width;
	ImageSize& operator= (ImageSize& size);
};

class Image
{
public:
	Image();
	Image(Image& image);
	Image(std::string path_);
	Image(char* path_);


	virtual std::string getPath();        //path setters & getter
	virtual void setPath(char* path_);
	virtual void setPath(std::string path_);

	virtual ImageSize getSize();
	virtual void setSize(int width, int height);
	virtual void setSize(ImageSize size_) ;

	virtual std::string getFormat();  //format getter (set automatico)


protected:
	std::string path; 	
	std::string format;
	ImageSize size;
	
};