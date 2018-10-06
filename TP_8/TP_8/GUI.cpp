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

bool GUI::createUI(unsigned int ImagesPerPage_  ,unsigned int dWidth , unsigned int dHeight )
{
	if (!usrImgs.empty())
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
		if (eventQueue == NULL && retVal)
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
		displaySize.height = dHeight;
		displaySize.width = dWidth;
		imagesPerPage = ImagesPerPage_;
		configOnScreenImgs();
		refresh();
		return UIcreated = retVal;
	}
	else
	{
		allegroError.setErrType(ErrType::NO_IMAGES_ADDED);
		allegroError.setErrDetail(string("Cannot create UI if no images are loaded\n"));
		return false;
	}
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

EventType GUI::needToRefresh()
{
	if (UIcreated)
	{
		//chequear que el evento sea reelevante
		//devolver el tipo de evento
		//return !al_is_event_queue_empty(eventQueue);
	}
	else
	{
		allegroError.setErrType(ErrType::UI_NOT_CREATED);
		allegroError.setErrDetail(string("Attempted operation while GUI not created \n") );
	}
	return EventType::ADD_POSSIBLE;//esta para que compile 
}

void GUI::refresh()
{
	if (UIcreated)
	{
		
		clearDisplay();
		drawBackround();
		drawImages();
		drawScreenInterface();
		al_flip_display();
	}
	else
	{
		allegroError.setErrType(ErrType::UI_NOT_CREATED);
		allegroError.setErrDetail(string("Attempted operation while GUI not created \n"));
	}

}

bool GUI::finished()
{
	return !done;
}

bool GUI::addImage(std::string path)
{	
	usrImgs.push_back(new AllegroImage(path));
	if (usrImgs.back()->errorOcurred())
	{
		allegroError.setErrType(ErrType::ALLEGRO_FAILED_IMAGE_LOAD);
		allegroError.setErrDetail(string("Failed to load image at ") + path + '\n');
		return false;
	}
	return true;
}

Error & GUI::getError()
{
	return allegroError;
}

vector<Image*>* GUI::getSelectedImages()
{
	if (!usrImgs.empty())
	{
		for (AllegroImage* image : usrImgs)
		{
			if (image->isSelected())
			{
				selectedImgs.push_back(image);
			}
		}
		return &selectedImgs;
	}
	else
	{
		allegroError.setErrType(ErrType::NO_IMAGES_ADDED);
		allegroError.setErrDetail(string("No saved images \n"));
		return nullptr;
	}
}

void GUI::clearDisplay()
{
	al_clear_to_color(al_map_rgb(0,0,0));
}

void GUI::drawScreenInterface()
{
	//FALTA!!
}

bool GUI::allegroInit() //inicializa modulos de allegro usados
{
	bool retVal;
	if (al_init())
	{
		if (al_init_image_addon())
		{			
			if (al_install_keyboard())
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

void GUI::configOnScreenImgs()
{
	for (vector<AllegroImage*>::iterator it = usrImgs.begin(); it != usrImgs.end() && (*it) != usrImgs[imagesPerPage]; ++it) //todas las imagenes hasta que se termine el arreglo o llegue a la maxima cantidad van a la pantalla
	{
		(*it)->toggleOnDisplay();
	}
}

void GUI::drawBackround()
{
	al_draw_scaled_bitmap(backround,
		0, 0,
		al_get_bitmap_width(backround), al_get_bitmap_height(backround),
		0, 0,
		displaySize.width, displaySize.height, 0
	);
}

void GUI::drawImages()
{
	
	
}
