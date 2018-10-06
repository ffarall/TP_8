#include "Compressor.h"
#include <iostream>

int main(void)
{
	//
	Compressor hola;
	if (hola.decode("test.eda"))
	{
		std::cout << "se pudo imprimir\n";
	}
	else
	{
		std::cout << "murio intentando descomprimir\n";
	}
	std::cout << "fin de la trasmision...\n";
	return 0;
}