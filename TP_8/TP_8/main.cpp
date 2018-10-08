#include "Compressor.h"
#include "GUI.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost::filesystem;

int main(int argc, char* argv[])
{
	GUI ui;
	path p(argv[2]);  //estaria tomando el path suponiendo que llega como segundo parametro
	string path;
	if (exists(p))
	{
		if (is_regular_file(p))
			cout << p << " is not a directory to find files " << '\n';
		else if (is_directory(p))
		{
			/* Si es un directorio busco los archivos que necesite*/
			for (directory_iterator itr(p); itr != directory_iterator(); itr++)
			{
				if (itr->path().extention().c_str() == ".png") // identifico si es png
				{
					ui.addImage(itr->path().string());
				}
			}
		}
	}
	else
		cout << p << "No existe\n";
	getchar();

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