#pragma once
#include<iostream>
#include"Image.h"
#include"allegro5/allegro.h"


class AllegroImage : public Image
{
public:
	AllegroImage();
	AllegroImage(std::string path_);

	virtual void setPath(std::string path_);


	ALLEGRO_BITMAP* getBitmap();

	void toggleSelect();

private:
	ALLEGRO_BITMAP* bitmap;
	bool selected;

};

