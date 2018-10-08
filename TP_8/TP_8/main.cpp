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
using namespace boost::filesystem;


struct util {
	string path;
	double threshold;
	bool mode; //true comprimir, false descomprimir
};

int main(int argc, char* argv[])
{
	util datosCmd;
	
	int error = parseCmdLine(argc, argv, [](char * key, char * value, void* userData) {
		util* externdata = (util *)userData;
		int error=0;
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
				error = 1;
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
			error = 1;

		return error;
	}, &datosCmd);
	
	if (error)
	{
		//how to use
		return 0;
	}
	
	GUI ui;
	path p(datosCmd.path);
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
				if (datosCmd.mode) // quiero descomprimir 
				{
					if (str_cmp(itr->path().extention().c_str(), ".png")) // identifico si es png
					{
						ui.addImage(itr->path().string());
					}
				}
				else //quiero comprimir
				{
					if (str_cmp(itr->path().extention().c_str(),".eda")) // identifico si es mi extencion
					{
						ui.addImage(itr->path().string());
					}
				}
			}
		}
	}
	else
		cout << p << "No existe\n";
	getchar();

	ui.createUI(9);

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
		string path((*imagen).getPath() + string(".") + (*imagen).getFormat);
		Compressor temp(path.c_str(), datosCmd.threshold);
		temp.encode((*imagen).getPath().c_str());
	}

	getchar();
	return 0;
}