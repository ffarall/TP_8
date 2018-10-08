#include "AllegroImage.h"
using namespace std;

#define DEFAULT_IMAGE "default.png"
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
		bitmap = al_load_bitmap(DEFAULT_IMAGE);
		if (bitmap == NULL)
		{
			isOk = false;
		}
		else
		{
			isOk = true;
			selected = false;
			onDisplay = false;
		}
	}
	else
	{
		isOk = true;
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
		bitmap = al_load_bitmap(DEFAULT_IMAGE);
		if (bitmap == NULL)
		{
			isOk = false;
		}
		else
		{
			isOk = true;
			selected = false;
			onDisplay = false;
		}
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

bool AllegroImage::isSelected()
{
	return selected;
}

void AllegroImage::select()
{
	selected = true;
}

void AllegroImage::deselect()
{
	selected = false;
}

bool AllegroImage::isOnDisplay()
{
	return onDisplay;
}

void AllegroImage::toggleSelect()
{
	selected = !selected;
}

void AllegroImage::toggleOnDisplay()
{
	onDisplay = !onDisplay;
}

bool AllegroImage::errorOcurred()
{
	return !isOk;
}


