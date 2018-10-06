#include "AllegroImage.h"
using namespace std;
AllegroImage::AllegroImage():Image()
{
	selected = false;
	onDisplay = false;
	bitmap = nullptr;
	isOk = false;
}

AllegroImage::AllegroImage(std::string path_):Image(path_)
{
	bitmap = al_load_bitmap(path_.c_str());
	if (bitmap == NULL)
	{
		isOk = false;
	}
	else
	{
		selected = false;
		onDisplay = false;
	}
}

AllegroImage::~AllegroImage()
{
	if (isOk)
	{
		al_destroy_bitmap(bitmap);
	}
}

void AllegroImage::setPath(std::string path_)
{
	bitmap = al_load_bitmap(path_.c_str());
	if (bitmap == NULL)
	{
		isOk = false;
	}
	else
	{
		size.height = al_get_bitmap_height(bitmap);
		size.width = al_get_bitmap_width(bitmap);
		path = path_;
		format = path.substr(path.find_last_of('.') + 1); //busco ultimo punto y a partir de ahi es el formato de la imagen
	}
}

ALLEGRO_BITMAP * AllegroImage::getBitmap()
{
	return bitmap;
}

void AllegroImage::toggleSelect()
{
	selected != selected;
}

void AllegroImage::toggleOnDisplay()
{
	onDisplay != onDisplay;
}

bool AllegroImage::errorOcurred()
{
	return !isOk;
}

