#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include"allegro5/display.h"
#include"Error.h"
#include"AllegroImage.h"
#include<vector>



class GUI
{
public:
	GUI();
	~GUI();
	bool createUI();
	bool closeUI();
	bool needToRefresh();
	void refresh();
	bool finished();

private:
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* fpsTimer;
	Error allegroError;
	unsigned int FPS;
	std::vector<AllegroImage> usrImages;
	ALLEGRO_BITMAP* backround;
	


};