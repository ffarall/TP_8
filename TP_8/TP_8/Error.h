#pragma once
#include<iostream>

enum class ErrType{NO_ERROR};//AGREGAR TODOS LOS TIPOS DE ERRORES
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