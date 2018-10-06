#include "Compressor.h"
#include "Image.h"
#include "lodepng.h"
#include <cmath>
#include <fstream>

#define MY_FILE_EXTENTION "eda"


Compressor::Compressor() : pixelMatrix() , compressorError()
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
		unsigned error = lodepng_decode32_file(&tempArray, &n, &tempN, dataArray);
		if ( error != 0)
		{
			compressorError.setErrType(ErrType::ERROR_PNG);
			compressorError.setErrDetail(string(lodepng_error_text(error)));
		}
		else
		{
			init((char *)tempArray, n);
		}
	}

	threshold = threshold_ * 255 / 100;
	
}


Compressor::~Compressor()
{
}

void Compressor::init(char * dataArray, int n_)
{
	n = n_;
	for (unsigned int i = 0; i < n * n; i++)
	{
		pixelMatrix.push_back(Pixel(*(dataArray + i + 1), *(dataArray + i + 2), *(dataArray + i + 3), *(dataArray + i + 4)));	// Add n*n Pixels initialised with (red, green, blue, alfa).
	}
}

bool Compressor::encode(const char * filename)
{
	compressedFile.open(filename);
	uint32_t imageSize = n * n * 4;				// There are n*n pixels, each containing 4 bytes. 
	compressedFile << imageSize;				// First 4 bytes of the file determine the size. 

	if (n == 1)
	{
		compressedFile << getPixel(0, 0).getR() << getPixel(0, 0).getG() << getPixel(0, 0).getB() << getPixel(0, 0).getAlpha();		// Borderline case: if the image is 1 pixel in size.
		return true;
	}
	compressedFile << 'N';						// After the size, comes the first node, whenever the image is bigger than 1 pixel. 

	return (encodeRec(n / 2, 0, n / 2) && encodeRec(0, 0, n / 2) && encodeRec(0, n / 2, n / 2) && encodeRec(n / 2, n / 2, n / 2));
}

bool Compressor::decode(const char * filename)
{
	string file(filename);
	uint16_t c;
	uint32_t size = 0;

	if (file.substr(file.find_last_of('.') + 1) != MY_FILE_EXTENTION)
	{
		return false; // if a wrong file is recieved, an error is sent 
	}

	fstream archivo;
	archivo.open(filename, fstream::in | fstream::out);
	if (!archivo.is_open())
	{
		return false; //if is not posible to open de file, return error
	}

	for (int i = 0; i < 4; i++) // tomo los primeros cuatro bytes para determinar la cantidad de pixeles qeu tendra la imagen
	{
		size <<= 8;
		c = archivo.get();
		if (c == EOF)
		{
			return false;
		}
		size |= (c & 0x00FF);
	}

	pixelMatrix.resize(size); //genero el vector de pixels

	n = (unsigned int)sqrt(size); //guardo el tama�o


	//dejo todo listo para empezar la recursion

	decodeRec(archivo, n / 2, 0, n);

	//en el vector pixel tengo todos los valores que tengo que pasar a char* para el encode32
	vector<unsigned char> image;
	image.resize(size * 4);
	for (unsigned y = 0; y < n; y++)
	{
		for (unsigned x = 0; x < n; x++)
		{
			image[4 * n * y + 4 * x + 0] = getPixel(x, y).getR();
			image[4 * n * y + 4 * x + 1] = getPixel(x, y).getG();
			image[4 * n * y + 4 * x + 2] = getPixel(x, y).getB();
			image[4 * n * y + 4 * x + 3] = getPixel(x, y).getAlpha();
		}
	}

	size_t x = file.find_last_of('\\');
	string exitName = file.substr(x == file.npos ? 0 : x, file.find_last_of('.') + 1) + "png"; // el png tendra el mismo nombre que el comprimido
	unsigned error = lodepng_encode32_file(exitName.c_str(), &(*image.begin()), n, n);

	if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;

	archivo.close();
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
		Pixel p(r, g, b, alpha);

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
		decodeRec(fp, x-(ancho/2), y+(ancho/2), ancho / 2); //cuadrante 3
		decodeRec(fp, x, y+(ancho/2) , ancho / 2); //cuadrante 4
	}

	return true;
}

bool Compressor::encodeRec(int x, int y, int n_)
{
	Pixel maxPixel;
	Pixel minPixel(255, 255, 255, 255);
	Pixel tempPixel;

	for (int i = 0; i < n_; i++)
	{
		for (int j = 0; j < n_; j++)
		{
			tempPixel = getPixel(x + j, y + i);

			if (maxPixel.getR() < tempPixel.getR())
			{
				maxPixel.setR(tempPixel.getR());
			}
			if (minPixel.getR() > tempPixel.getR());
			{
				minPixel.setR(tempPixel.getR());
			}
			if (maxPixel.getG() < tempPixel.getG())
			{
				maxPixel.setG(tempPixel.getG());
			}
			if (minPixel.getG() > tempPixel.getG());
			{
				minPixel.setG(tempPixel.getG());
			}
			if (maxPixel.getB() < tempPixel.getB())
			{
				maxPixel.setB(tempPixel.getB());
			}
			if (minPixel.getB() > tempPixel.getB());
			{
				minPixel.setB(tempPixel.getB());
			}
			if (maxPixel.getAlpha() < tempPixel.getAlpha())
			{
				maxPixel.setAlpha(tempPixel.getAlpha());
			}
			if (minPixel.getAlpha() > tempPixel.getAlpha());
			{
				minPixel.setAlpha(tempPixel.getAlpha());
			}
		}
	}

	double quadrantScore = sqrt(pow(maxPixel.getR() - minPixel.getR(), 2) + pow(maxPixel.getG() - minPixel.getG(), 2) + pow(maxPixel.getB() - minPixel.getB(), 2) + pow(maxPixel.getAlpha() - minPixel.getAlpha(), 2));

	if (quadrantScore < threshold)		// If the variation is less than the threshold established... 
	{
		compressedFile << 'H';														// The program arrived to a leave of the quad tree. 
		compressedFile << ((maxPixel.getR() + minPixel.getR()) / 2);				// Writing average RED to file. 
		compressedFile << ((maxPixel.getG() + minPixel.getG()) / 2);				// Writing average GREEN to file. 
		compressedFile << ((maxPixel.getB() + minPixel.getB()) / 2);				// Writing average BLUE to file. 
		compressedFile << ((maxPixel.getAlpha() + minPixel.getAlpha()) / 2);		// Writing average ALPHA to file. 
		return true;
	}
	else
	{
		compressedFile << 'N';				// Since the variation is higher than the threshold, a new node is created. 
		return (encodeRec(n / 2, 0, n / 2) && encodeRec(0, 0, n / 2) && encodeRec(0, n / 2, n / 2) && encodeRec(n / 2, n / 2, n / 2));
	}
}

bool Compressor::isOk(void)
{
	return (compressorError.getErrType() == ErrType::NO_ERROR);
}

string Compressor::getError(void)
{
	return compressorError.getErrDetail();
}

