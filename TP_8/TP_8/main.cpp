#include "Compressor.h"
#include <iostream>

int main(int argc, char* argv[])
{
	//
	Compressor hola;
	if (hola.encode("test.png"))
	{

		if (hola.decode("test.eda"))
		{
			std::cout << "se pudo imprimir\n";
		}
		else
		{
			std::cout << "murio intentando descomprimir\n";
		}
		std::cout << "fin de la descompresion...\n";
		getchar();
	
	}

	return 0;
}