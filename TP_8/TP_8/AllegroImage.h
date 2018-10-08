#pragma once
#include<iostream>
#include"Image.h"
#include"allegro5/allegro.h"
#include"Error.h"



class AllegroImage : public Image
{
public:
	AllegroImage();
	AllegroImage(std::string path_);
	~AllegroImage();

	virtual void setPath(std::string path_);


	ALLEGRO_BITMAP* getBitmap();
	bool isSelected();
	void select();
	void deselect();
	bool isOnDisplay();
	void toggleSelect();
	void toggleOnDisplay();
	bool errorOcurred();

private:
	ALLEGRO_BITMAP* bitmap;
	bool selected;
	bool onDisplay;
	bool isOk;
};

