#include "Compressor.h"
#include "Image.h"
#include "lodepng.h"
#include <cmath>
#include <fstream>

#define MY_FILE_EXTENTION "eda"


Compressor::Compressor() : pixelMatrix()
{
	n = 0;
}

Compressor::Compressor(char * dataArray, double threshold_) : pixelMatrix()
{
	Image png(dataArray);
	
	unsigned char * tempArray; //si es un png estas las utilizo en lodepng functios
	unsigned int tempN;

	if (png.getFormat() == "png")
	{
		if (lodepng_decode32_file(&tempArray, &n, &tempN, dataArray) != 0)
		{
			//es un error;
		}
		else
		{
			init((char *)tempArray, n);
		}
	}
	
}


Compressor::~Compressor()
{
}

void Compressor::init(char * dataArray, int n_)
{
	n = n_;
	for (unsigned int i = 0; i < n * n; i++)
	{
		pixelMatrix.push_back(Pixel(dataArray + i + 1, dataArray + i + 2, dataArray + i + 3, dataArray + i + 4));	// Add n*n Pixels initialised with (red, green, blue, alfa).
	}
}

bool Compressor::decode(const char * filename)
{
	string file(filename);
	uint16_t c, d, e ,f;
	
	if (file.substr(file.find_last_of('.') + 1) != MY_FILE_EXTENTION)
	{
		return false; // if a wrong file is recieved, an error is sent 
	}
	
	fstream archivo;
	archivo.open(filename, fstream::in | fstream::out );
	if (!archivo.is_open())
	{
		return false; //if is not posible to open de file, return error
	}

	c = archivo.get(); // tomo los primeros dos chars, que corresponden al size de la imagen
	d = archivo.get();
	e = archivo.get();
	f = archivo.get();
	if (c == EOF || d == EOF || e == EOF || f == EOF)// me fijo que sean caracteres validos
	{
		return false;
	}

	uint32_t size = (((c << 8) & 0xFF00) | (d & 0x00FF));// armo el valor de size
	size <<= 16;
	size |= (((e << 8) & 0xFF00) | (f & 0x00FF));
	pixelMatrix.resize(size); //genero el vector de pixels

	n = (unsigned int)sqrt(size);

	/*c = archivo.get();
	if (c != 'n' && c != 'N') // si despues de ¿l tamaño no tengo una N esta mal comprimido el archivo
	{
		return false;
	}*/
	
	//dejo todo listo para empezar la recursion

	decodeRec(archivo, n / 2, 0, n);

	//en el vector pixel tengo todos los valores que tengo que pasar a char* para el encode32
	unsigned char * dataFinalPNGNew = new unsigned char[size*4];
	int cont = 0;
	for (Pixel a : pixelMatrix )
	{
		*(dataFinalPNGNew+cont) = a.getR();
		*(dataFinalPNGNew+ cont + 1) = a.getG();
		*(dataFinalPNGNew+ cont + 2) = a.getB();
		*(dataFinalPNGNew+ cont + 3) = a.getAlpha();
		cont++;
	}
	
	lodepng_encode32_file("nombre.png", dataFinalPNGNew, n, n); // cambiar lo de nombre.png
	
	archivo.close();
	delete []dataFinalPNGNew ;
	return true;
}

Pixel Compressor::getPixel(int x, int y)
{
	int element = y * n + x;
	return pixelMatrix[element];
}

bool Compressor::setPixel(Pixel& pixel_, unsigned int x, unsigned int y)
{
	int element;
	if (x < n && y < n) //compruebo que el pixel este dentro de la matriz
	{
		element = y * n + x;
		pixelMatrix[element] = pixel_;
	}
	return false; // no se pudo escribir el pixel
}

bool Compressor::decodeRec(fstream& fp, int x, int y, int ancho)
{
	unsigned short c = fp.get();
	char r, g, b, alpha;
	if (c == 'H') // tengo que pintar
	{
		r = (char)fp.get();
		g = (char)fp.get();
		b = (char)fp.get();
		alpha = (char)fp.get();
		Pixel p(&r, &g, &b, &alpha);

		for (int i = 0; i < ancho; i++) //pinto una serir de pixels
		{
			for (int j = 0; j < ancho; j++)
			{
				setPixel(p, x + i, y + j);
			}
		}
	}
	else if(c == 'N')
	{
		decodeRec(fp, x, y, ancho / 2); //cuadrante 1
		decodeRec(fp, x-(ancho/2), y, ancho / 2); //cuadrante 2
		decodeRec(fp, x-(ancho/2), y+(ancho/2), ancho / 2); //cuandrante 3
		decodeRec(fp, x, y+(ancho/2) , ancho / 2); //cuadrante 4
	}

	return true;
}


