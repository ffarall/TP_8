#pragma once
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include"allegro5/display.h"
#include"Error.h"
#include"AllegroImage.h"
#include<vector>

#define DWIDTH  1000 //DEFAULT DISPLAY SIZE
#define DHEIGHT 600
#define DEFAULT_PAGE_IMAGES 9 


class DisplaySize
{
public:
	unsigned int width;
	unsigned int height;
};
enum class EventType{ADD_POSSIBLE, EVENTS, HERE};
class GUI
{
public:
	GUI(); //constructor y destructo de la clase
	~GUI();


	bool createUI(unsigned int ImagesPerPage_ = DEFAULT_PAGE_IMAGES, unsigned int dWidth = DWIDTH, unsigned int dHeight = DHEIGHT);
	void closeUI();
	EventType needToRefresh();
	void refresh();
	bool finished();	
	bool addImage(std::string path);
	Error& getError();
	std::vector<Image*>* getSelectedImages();

private:
	ALLEGRO_EVENT_QUEUE* eventQueue;
	ALLEGRO_DISPLAY* display;
	Error allegroError;
	ALLEGRO_BITMAP* backround;
	DisplaySize displaySize;
	
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
	

};