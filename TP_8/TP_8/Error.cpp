#include "Error.h"
using namespace std;
Error::Error()
{
	errorType = ErrType::NO_ERROR;
	errorDetail = string("NO_ERROR DEFAULT STRING");
}

ErrType Error::getErrType()
{
	return errorType;
}



void Error::setErrType(ErrType type)
{
	errorType = type;
	
	switch (errorType)
	{
	case ErrType::NO_ERROR :
		errorDetail = "NO_ERROR DEFAULT STRING";
		break;

	case ErrType::ALLEGRO_DISPLAY_ERROR : case ErrType::ALLEGRO_FAILED_IMAGE_LOAD : case ErrType::ALLEGRO_INIT_ERROR : case ErrType::ALLEGRO_QUEUE_ERROR :
		errorDetail = "PROBLEMS WITH GRAFIC LIBRARY";
		break;

	case ErrType::NO_IMAGES_ADDED:
		errorDetail = "NO IMAGES IN THIS FOLDER";
		break;

	case ErrType::UI_NOT_CREATED :
		errorDetail = "USER INTERFACE NOT CREATED";
		break;
	
	case ErrType::ERROR_PNG:
		errorDetail = "ERROR WHILE WORKING WITH PNG FILE";
		break;
	}
}

std::string Error::getErrDetail()
{
	return errorDetail;
}

void Error::setErrDetail(std::string detail)
{
	errorDetail = detail;
}
