#pragma once
#include<iostream>


class ImageSize
{
public:
	int height;
	int width;
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
	virtual void setSize(int width, int heigth);
	virtual void setSize(ImageSize size_);

	virtual std::string getFormat();  //format getter (set automatico)


private:
	std::string path; 	
	std::string format;
	ImageSize size;
	
};