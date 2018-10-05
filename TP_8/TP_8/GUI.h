#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include"allegro5/display.h"




class GUI
{
public:
	void refresh();
	bool createUI();
	bool closeUI();




private:
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* fpsTimer;
	unsigned int FPS;
	


};