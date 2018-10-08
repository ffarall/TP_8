#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include"allegro5/display.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include"Error.h"
#include"AllegroImage.h"
#include<vector>

#define DWIDTH  1000 //DEFAULT DISPLAY SIZE
#define DHEIGHT 600
#define PAGE_IMAGES 9 


class DisplaySize
{
public:
	unsigned int width;
	unsigned int height;
};
enum class EventType{ERROR = -1, NO_EVENTS};
class GUI
{
public:
	GUI(); //constructor y destructo de la clase
	~GUI();


	bool createUI( unsigned int dWidth = DWIDTH, unsigned int dHeight = DHEIGHT);
	void closeUI();
	bool needToRefresh();
	void refresh();
	bool finished();	
	bool addImage(std::string path);
	Error& getError();
	std::vector<Image*>* getSelectedImages();

private:
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_BITMAP* backround;
	ALLEGRO_BITMAP* checkedBox;
	ALLEGRO_BITMAP* uncheckedBox;
	ALLEGRO_FONT* imageNameFont;
	ALLEGRO_FONT* titleFont;
	Error allegroError;
	DisplaySize displaySize;
	EventType eventType;
	
	std::vector<AllegroImage*> usrImgs;	
	std::vector<Image*> selectedImgs;

	unsigned int imagesPerPage;
	unsigned int currentPage;


	bool UIcreated;   //si la UI fue creada o no
	bool done;

	bool allegroInit();
	void allegroDestroy();
	void configOnScreenImgs();
	void clearDisplay();
	void drawScreenInterface();
	void drawBackround();
	void drawImages();
	bool filterEvent();
	unsigned int keyToImg(const char pressedKey);
	void turnPageLeft();
	void turnPageRight();
	void selectAll();
	void deselectAll();
	const char* pathToName(std::string path_);
	

};