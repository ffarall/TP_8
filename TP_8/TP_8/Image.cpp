#include "Image.h"
using namespace std;

Image::Image()
{

}

Image::Image(Image& image)
{
	path = image.getPath();
	format = image.getFormat();
}

Image::Image(std::string path_)
{
	path = path_;
	format = path.substr(path.find_last_of('.') + 1); //busco ultimo punto y a partir de ahi es el formato de la imagen
}

Image::Image(char * path_)
{
	Image(string(path_));
}

std::string Image::getPath()
{
	return path;
}

void Image::setPath(char * path_)
{
	path = string(path_);
}

void Image::setPath(std::string path_)
{
	path = path_;
}



std::string Image::getFormat()
{
	return format;
}

