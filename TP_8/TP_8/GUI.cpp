#include "GUI.h"
#include"allegro5/allegro.h"
#include"allegro5/allegro_image.h"
#include"allegro5/allegro_font.h"
#include"allegro5/allegro_color.h"
#include"allegro5/allegro_ttf.h"



#define IMAGE_NAME_FONT_PATH "imageName.ttf"
#define IMAGE_NAME_FONT_SIZE 10
#define TITLE_FONT_PATH "titleFont.ttf"
#define TITLE_FONT_SIZE 30
#define BACKROUND_PATH "backround.png"
#define CHECKED_BOX_PATH "checkedBox.png"
#define UNCHECKED_BOX_PATH "uncheckedBox.png"
#define X_START(x) (0.08 * (x))
#define Y_START(x) (0.2 * (x))
#define IMAGE_SPACE 10
#define MAX_NAME_CHARS 10
#define PX_CORRECT 10

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
	for (vector<AllegroImage*>::iterator it = usrImgs.begin(); it != usrImgs.end() && (*it) != usrImgs[imagesPerPage]; ++it)
	{
		delete (*it);
	}
	usrImgs.clear();
	selectedImgs.clear();
}

bool GUI::createUI(unsigned int dWidth , unsigned int dHeight )
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
		checkedBox = al_load_bitmap(CHECKED_BOX_PATH);
		if (checkedBox == NULL && retVal)
		{
			allegroError.setErrType(ErrType::ALLEGRO_FAILED_IMAGE_LOAD);
			allegroError.setErrDetail(string("Failed to load backround at ") + CHECKED_BOX_PATH + '\n');
			retVal = false;
			al_destroy_event_queue(eventQueue);
			al_destroy_display(display);
			al_destroy_bitmap(backround);

		}
		uncheckedBox = al_load_bitmap(UNCHECKED_BOX_PATH);
		if (uncheckedBox == NULL && retVal)
		{
			allegroError.setErrType(ErrType::ALLEGRO_FAILED_IMAGE_LOAD);
			allegroError.setErrDetail(string("Failed to load backround at ") + UNCHECKED_BOX_PATH + '\n');
			retVal = false;
			al_destroy_event_queue(eventQueue);
			al_destroy_display(display);
			al_destroy_bitmap(backround);
			al_destroy_bitmap(checkedBox);

		}
		imageNameFont = al_load_ttf_font(IMAGE_NAME_FONT_PATH,IMAGE_NAME_FONT_SIZE,0);
		if (imageNameFont == NULL && retVal)
		{
			allegroError.setErrType(ErrType::ALLEGRO_FAILED_FONT_LOAD);
			allegroError.setErrDetail(string("Failed to load font at ") + IMAGE_NAME_FONT_PATH + '\n');
			retVal = false;
			al_destroy_event_queue(eventQueue);
			al_destroy_display(display);
			al_destroy_bitmap(backround);
		}
		titleFont = al_load_ttf_font(TITLE_FONT_PATH, TITLE_FONT_SIZE, 0);
		if (titleFont == NULL)
		{
			allegroError.setErrType(ErrType::ALLEGRO_FAILED_FONT_LOAD);
			allegroError.setErrDetail(string("Failed to load font at ") + TITLE_FONT_PATH + '\n');
			retVal = false;
			al_destroy_event_queue(eventQueue);
			al_destroy_display(display);
			al_destroy_bitmap(backround);
			al_destroy_font(imageNameFont);
		}
		displaySize.height = dHeight;
		displaySize.width = dWidth;
		imagesPerPage = PAGE_IMAGES;
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
		al_destroy_font(imageNameFont);
		al_destroy_font(titleFont);
	}
}

bool GUI::needToRefresh()
{
	if (UIcreated)
	{
		return !al_is_event_queue_empty(eventQueue);
	}
	else
	{
		allegroError.setErrType(ErrType::UI_NOT_CREATED);
		allegroError.setErrDetail(string("Attempted operation while GUI not created \n") );
		return false;
	}
}

void GUI::refresh()
{
	if (UIcreated)
	{	
		if (filterEvent())
		{
			clearDisplay();
			drawBackround();
			drawImages();
			drawScreenInterface();
			al_flip_display();
		}
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
	if (!UIcreated)
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
	else
	{
		allegroError.setErrType(ErrType::UI_CREATED);
		allegroError.setErrDetail(string("Cannot add images once UI is created\n"));
		return false;
	}
}

Error & GUI::getError()
{
	return allegroError;
}

vector<Image*>* GUI::getSelectedImages()
{
	if (!usrImgs.empty())
	{
		for (vector<AllegroImage*>::iterator it = usrImgs.begin(); it != usrImgs.end(); it++)
		{
			if ((*it)->isSelected())
			{
				selectedImgs.push_back((*it));
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
	
	//ver en que pagina estas, dibujar flechitas. dibujar pagina 1/n. titulo?
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
				if (al_init_font_addon())
				{
					if (al_init_ttf_addon)
					{
						retVal = true;
					}
					else
					{
						allegroError.setErrType(ErrType::ALLEGRO_INIT_ERROR);
						allegroError.setErrDetail(string("Error while trying to install TTF ADDON\n"));
						al_shutdown_image_addon();
						al_shutdown_font_addon();
						al_uninstall_keyboard();
						retVal = false;
					}
				}
				else
				{
					allegroError.setErrType(ErrType::ALLEGRO_INIT_ERROR);
					allegroError.setErrDetail(string("Error while trying to install FONT ADDON\n"));
					al_shutdown_image_addon();
					al_uninstall_keyboard();
					retVal = false;
				}
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
		al_shutdown_font_addon();
		al_shutdown_ttf_addon();
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
	bool error = false;
	for (int i = 0; i < imagesPerPage/3 && !error; i++)
	{
		for(int j = 0; j<imagesPerPage/3 && !error ;j++)
		{
			if ((i * 3 + j) < usrImgs.size())
			{
				ALLEGRO_BITMAP* currBitmap = usrImgs[i * 3 + j]->getBitmap();
				al_draw_scaled_bitmap(currBitmap,
					0, 0,
					al_get_bitmap_width(currBitmap), al_get_bitmap_height(currBitmap),
					X_START(displaySize.width) + ((IMAGE_SPACE + 0.82*displaySize.width / 3)*j), Y_START(displaySize.height) + ((IMAGE_SPACE + 0.675*displaySize.height / 3)*i),
					(0.82*displaySize.width / 3) - 2 * IMAGE_SPACE, (0.675*displaySize.height / 3) - 2 * IMAGE_SPACE, 0
				);
				al_draw_text(imageNameFont, al_map_rgb(0, 0, 0), X_START(displaySize.width) + ((IMAGE_SPACE + 0.82*displaySize.width / 3)*j), Y_START(displaySize.height) + ((IMAGE_SPACE + 0.675*displaySize.height / 3)*(i + 1)), 0, pathToName(usrImgs[i * 3 + j]->getPath()));

				if (usrImgs[i * 3 + j]->isSelected)
				{
					al_draw_bitmap(checkedBox, (X_START(displaySize.width) + ((IMAGE_SPACE + 0.82*displaySize.width / 3)*j))+PX_CORRECT, (Y_START(displaySize.height) + ((IMAGE_SPACE + 0.675*displaySize.height / 3)*i))+PX_CORRECT,0);
				}
				else
				{

				}
			}
			else
			{
				error = true;
			}
		}
	}
	
	
}

bool GUI::filterEvent()
{
	bool retVal;
	ALLEGRO_EVENT* receivedEv;
	al_get_next_event(eventQueue, receivedEv);
	switch (receivedEv->type)
	{
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		done = true;
		closeUI();
		retVal= false;
		break;
	case ALLEGRO_EVENT_KEY_UP:
		switch (receivedEv->keyboard.keycode)
		{
		case ALLEGRO_KEY_LEFT:
			turnPageLeft();
			retVal = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			turnPageRight();
			retVal = true;
			break;
		case ALLEGRO_KEY_A:
			selectAll();
			retVal = true;
			break;
		case ALLEGRO_KEY_N:
			deselectAll();
			retVal = true;
			break;
		case ALLEGRO_KEY_ENTER:
			done = true;
			closeUI();
			retVal = false;
			break;
		default:
			retVal = false;
			break;
		}		
		break;
	case ALLEGRO_EVENT_KEY_CHAR:
		if (receivedEv->keyboard.unichar >= '1' && receivedEv->keyboard.unichar <= '9')
		{
			usrImgs[keyToImg(receivedEv->keyboard.unichar)]->toggleSelect();
			retVal = true;
		}
		break;
	default:
		retVal = false;
		break;
	}
	return retVal;
}

unsigned int GUI::keyToImg(const char pressedKey)
{
	unsigned int image = pressedKey - '1';
	image += currentPage * imagesPerPage;
	return image;
}

void GUI::turnPageLeft()
{
	if (currentPage != 0)
	{
		int i = 0;
		while (!usrImgs[i++]->isOnDisplay());
		for (int j = i-imagesPerPage; j < i + imagesPerPage && j < usrImgs.size(); j++)
		{
			usrImgs[j]->toggleOnDisplay;
		}
	}
}

void GUI::turnPageRight()
{
	if(currentPage<(usrImgs.size()/imagesPerPage))
	{
		int i = 0;
		while (!usrImgs[i++]->isOnDisplay());
		for (int j = i ; j < i + 2*imagesPerPage && j < usrImgs.size(); j++)
		{
			usrImgs[j]->toggleOnDisplay;
		}
	}
}

void GUI::selectAll()
{

	for (vector<AllegroImage*>::iterator it = usrImgs.begin(); it != usrImgs.end(); it++)
	{
		(*it)->select();
	}
}

void GUI::deselectAll()
{
	for (vector<AllegroImage*>::iterator it = usrImgs.begin(); it != usrImgs.end(); it++)
	{
		(*it)->deselect();
	}
}

const char * GUI::pathToName(std::string path_)
{
	if (size_t pos = path_.find_last_of('\\') != string::npos && (pos - path_.find_last_of('.')) < MAX_NAME_CHARS)
	{
		return (path_.c_str())+pos;
	}
	else if(path_.size() < MAX_NAME_CHARS)
	{
		return path_.c_str();
	}
	else
	{
		return "name too long";
	}
	return nullptr;
}
