#include "GUI.h"
#include"allegro5/allegro.h"
#include"allegro5/allegro_image.h"
#include"allegro5/allegro_font.h"
#include"allegro5/allegro_color.h"

#define BACKROUND_PATH "backround.png"
using namespace std;
GUI::GUI()
{
	allegroInit();	
	usrImgs.clear();
	selectedImgs.clear();
	UIcreated = false;
}

GUI::~GUI()
{
	allegroDestroy();
	usrImgs.clear();
	selectedImgs.clear();
}

bool GUI::createUI(unsigned int dWidth = DWIDTH, unsigned int dHeight = DHEIGHT)
{
	bool retVal = true;
	display = al_create_display(dWidth, dHeight);
	if (display == NULL)
	{
		allegroError.setErrType(ErrType::ALLEGRO_DISPLAY_ERROR);
		allegroError.setErrDetail(string("Failed to create display\n"));
		retVal = false;
	}
	eventQueue = al_create_event_queue();
	if (eventQueue == NULL && retVal )
	{
		allegroError.setErrType(ErrType::ALLEGRO_QUEUE_ERROR);
		allegroError.setErrDetail(string("Failed to create event queue\n"));
		al_destroy_display(display);
		retVal = false;
	}
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	backround = al_load_bitmap(BACKROUND_PATH);
	if (backround == NULL && retVal)
	{
		allegroError.setErrType(ErrType::ALLEGRO_FAILED_IMAGE_LOAD);
		allegroError.setErrDetail(string("Failed to load backround at ") + BACKROUND_PATH + '\n');
		retVal = false;
		al_destroy_event_queue(eventQueue);
		al_destroy_display(display);

	}
	UIcreated = true;
	return retVal;
}

void GUI::closeUI()
{
	if (UIcreated)
	{
		al_destroy_display(display);
		al_destroy_event_queue(eventQueue);
		al_destroy_bitmap(backround);
	}

}

bool GUI::needToRefresh()
{
	return !al_is_event_queue_empty(eventQueue);
}

void GUI::refresh()
{
	clearDisplay();
	drawBackround();
	drawImages();
	drawScreenInterface();
	al_flip_display();
}

bool GUI::finished()
{
	return !done;
}

bool GUI::addImage(std::string path)
{
	//falta!!!!
	return false;
}

Error & GUI::getError()
{
	return allegroError;
}

vector<Image&>& GUI::getSelectedImages()
{
	// TODO: insert return statement here
	//FALTA!!!!
}

void GUI::clearDisplay()
{
	al_clear_to_color(al_map_rgb(0,0,0));
}

void GUI::drawScreenInterface()
{
	//FALTA!!!
}

bool GUI::allegroInit() //inicializa modulos de allegro usados
{
	bool retVal;
	if (al_init())
	{
		if (al_init_image_addon())
		{			
			if (al_install_keyboard)
			{
				retVal = true;
			}
			else
			{
				allegroError.setErrType(ErrType::ALLEGRO_INIT_ERROR);
				allegroError.setErrDetail(string("Error while trying to install KEYBOARD ADDON\n"));
				al_shutdown_image_addon();
				retVal = false;
			};
		}
		else
		{
			allegroError.setErrType(ErrType::ALLEGRO_INIT_ERROR);
			allegroError.setErrDetail(string("Error while trying to install IMAGE ADDON\n"));
			retVal = false;
		}		
	}
	else
	{
		allegroError.setErrType(ErrType::ALLEGRO_INIT_ERROR);
		allegroError.setErrDetail(string("Error while trying to install ALLEGRO\n"));
		retVal = false;
	}
	
	display = nullptr;
	backround = nullptr;
	eventQueue = nullptr;
	return retVal;
}

void GUI::allegroDestroy()
{
	if (allegroError.getErrType() != ErrType::ALLEGRO_INIT_ERROR)
	{
		al_shutdown_image_addon();
		al_uninstall_keyboard();
	}
}

bool GUI::drawBackround()
{
	if (backround != nullptr) //si ya esta seteado el backround lo dibujo, sino error
	{
		al_draw_scaled_bitmap(backround,
			0, 0,
			al_get_bitmap_width(backround), al_get_bitmap_height(backround),
			0, 0,
			displaySize.width, displaySize.height, 0
		);
		return true;
	}
	else
	{
		return false;
	}
}

bool GUI::drawImages()
{
	//FALTAAA
	return false;
}
