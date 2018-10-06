#include "Image.h"
using namespace std;

Image::Image()
{
	path = string("no path received");
	format = string("nothing");
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
	path = std::string(path_);
	format = path.substr(path.find_last_of('.') + 1); //busco ultimo punto y a partir de ahi es el formato de la imagen
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

ImageSize Image::getSize()
{
	return ImageSize();
}

void Image::setSize(int width, int height)
{
	size.height = height;
	size.width = width;

}

void Image::setSize(ImageSize size_)
{
	size = size_;
}



std::string Image::getFormat()
{
	return format;
}

ImageSize::ImageSize()
{
}

ImageSize::ImageSize(int height, int width)
{
	this->height = height;
	this->width = width;
}

ImageSize& ImageSize::operator=(ImageSize & size)
{
	if (this != &size)
	{
		this->height = size.height;
		this->width = size.width;
	}
	return *this;
}
