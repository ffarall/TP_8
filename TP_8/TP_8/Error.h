#pragma once
#include<iostream>

enum class ErrType{NO_ERROR, ALLEGRO_INIT_ERROR, ALLEGRO_DISPLAY_ERROR, ALLEGRO_QUEUE_ERROR, ALLEGRO_FAILED_IMAGE_LOAD
					, UI_NOT_CREATED, NO_IMAGES_ADDED, ERROR_PNG};//AGREGAR TODOS LOS TIPOS DE ERRORES
class Error
{
public:
	Error();

	ErrType getErrType();
	void setErrType(ErrType type);
	std::string getErrDetail();
	void setErrDetail(std::string detail);

private:
	ErrType errorType;
	std::string errorDetail;
};