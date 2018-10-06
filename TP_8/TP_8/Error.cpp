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
	
}

std::string Error::getErrDetail()
{
	return errorDetail;
}

void Error::setErrDetail(std::string detail)
{
	errorDetail = detail;
}
