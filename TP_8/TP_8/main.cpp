#include "Compressor.h"
#include <iostream>

int main(int argc, char* argv[])
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

	Compressor hola2("test.png", 5);
	if (hola.encode("test2"))
	{
		std::cout << "comprimió bien." << std::endl;
	}
	else
	{
		std::cout << "sorry bro, no comprimió bien" << std::endl;
	}
	std::cout << "fin de la trasmision...\n";
	getchar();
	return 0;
}