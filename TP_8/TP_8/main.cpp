#include "Compressor.h"
#include "GUI.h"
#include "Image.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>


extern "C" 
{
#include "parse.h"
}

using namespace std;
using namespace boost::filesystem;


void howToUse(void);
int callback(char * key, char * value, void* userData);

struct util {
	string path;
	double threshold;
	bool mode; //true comprimir, false descomprimir
};

int main(int argc, char* argv[])
{
	string a("C:\\Users\\arrib\\source\\repos\\TP_8\\TP_8\\TP_8\\fotos"); 
	//a.clear();
	util datosCmd = {a,0, false}; // por defecto tiene un threshold y comprime

	int error = parseCmdLine(argc, argv, callback , &datosCmd);
	
	if ( datosCmd.path.empty() || !error) // si no hubo error y recibi un path
	{
		std::cout << "error\n";
		howToUse();
		return 0;
	}
	
	GUI ui;
	path p(datosCmd.path);
	string path;

	if (exists(p))
	{
		if (is_regular_file(p))
		{
			std::cout << p << " is not a directory to find files " << '\n';
		}
		else if (is_directory(p))
		{
			/* Si es un directorio busco los archivos que necesite*/
			for (directory_iterator itr(p); itr != directory_iterator(); itr++)
			{
				if (datosCmd.mode) // quiero descomprimir 
				{
					if ( ((itr->path()).extension()) ==  ".png") // identifico si es png
					{
						ui.addImage(itr->path().string());
					}
				}
				else //quiero comprimir
				{
					if ((itr->path()).extension() == ".eda") // identifico si es mi extencion
					{
						ui.addImage(itr->path().string());
					}
				}
			}
		}
	}
	else
	{
		std::cout << p << "No existe\n";
	}

	cout << "Listo los archivos\n"; //hasta aca funciona, mas abajo muere en algun lado

	if (!ui.createUI())
	{
		std::cout << ui.getError().getErrDetail() << endl;
		return 0;
	}
	
	while (!ui.finished())
	{
		if (ui.needToRefresh())
		{
			ui.refresh();
		}
	}

	vector<Image *> imagenVector = *(ui.getSelectedImages());
	for (Image* imagen : imagenVector)
	{
		string path((*imagen).getPath());
		if (datosCmd.mode)
		{
			Compressor temp(path.c_str(), datosCmd.threshold);
			if(temp.isOk())
			{
				temp.encode(path.substr(0, path.find_last_of('.')).c_str());
			}
			else
			{
				std::cout << "Unable to compress: " << path << "\n";
				std::cout << temp.getError() << std::endl;
			}
			
		}
		else
		{
			Compressor temp2;
			temp2.decode(path.c_str());
		}
	}

	cout << "finito\nPresione enter para finalizar\n";
	getchar();
	return 0;
}

void howToUse(void)
{
	cout << "Se ha producido un error al intentar utilizar el compresor/descompresor\n";
	cout << "El programa funciona recibiendo dos opciones y un parametro: \n";
	cout << "\t-> -path y el directorio en el cual se encuetran los archivos que desea comprimir o descomprimir\n";
	cout << "\t-> -t y un numero entre 0 y 100 para indicar el threshold con el que se quiere comprimir";
	cout << "\t-> 'd' o 'c' si se desea descomprimir o comprimir respectivamente \n";
	cout << "Por favor ejecute denuevo el programa con los las variables correspondientes\n";
}

int callback(char * key, char * value, void* userData)
{
	util* externdata = (util *)userData;
	int error = 1;
	if (key == NULL) // indica descomprimir o comprimir
	{
		if (str_cmp(value, "c")) // quiero comprimir
		{
			externdata->mode = true;
		}
		else if (str_cmp(value, "d")) //quiero descomprimir
		{
			externdata->mode = false;
		}
		else
			error = 0;
	}
	else if (str_cmp(key, "path"))
	{
		externdata->path = string(value);
	}
	else if (str_cmp(key, "t"))
	{
		externdata->threshold = atof(value);
	}
	else
		error = 0;

	return error;
}