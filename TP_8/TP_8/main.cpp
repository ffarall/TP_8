#include "Compressor.h"
#include <iostream>

int main(int argc, char* argv[])
{
	//
	Compressor hola("test.png",2);
	if (hola.encode("veremos"))
	{
		std::cout << "se pudo comprimir\n";
		getchar();
		if (hola.decode("veremos.eda"))
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