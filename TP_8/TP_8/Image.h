#pragma once
#include<iostream>
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


	virtual std::string getFormat();  //format getter (set automatico)


private:
	std::string path; 	
	std::string format;
};