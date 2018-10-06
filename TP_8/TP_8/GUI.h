#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include"allegro5/display.h"
#include"Error.h"
#include"AllegroImage.h"
#include<vector>

#define DWIDTH  1000 //DEFAULT DISPLAY SIZE
#define DHEIGHT 600
class DisplaySize
{
public:
	unsigned int width;
	unsigned int height;
};

class GUI
{
public:
	GUI();
	~GUI();
	bool createUI(unsigned int dWidth = DWIDTH, unsigned int dHeight = DHEIGHT);
	void closeUI();
	bool needToRefresh();
	void refresh();
	bool finished();
	bool addImage(std::string path);
	Error& getError();
	std::vector<Image&>& getSelectedImages();

private:
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_DISPLAY* display;
	Error allegroError;
	ALLEGRO_BITMAP* backround;


	std::vector<AllegroImage> usrImgs;	
	std::vector<AllegroImage&> selectedImgs;


	bool UIcreated;   //si la UI fue creada o no
	void clearDisplay();
	void drawScreenInterface();
	bool allegroInit();
	void allegroDestroy();
	bool drawBackround();
	bool drawImages();
	DisplaySize displaySize;
	bool done;

};