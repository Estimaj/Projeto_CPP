#ifndef __Vertice__
#define __Vertice__

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <list>
#include <map>
#include "Objetos.h"
using namespace std;

class Vertice : public Objetos
{
	///Coordenadas Vertice
	double Coor_X;
	double Coor_Y;
	double Coor_Z;

public:

	Vertice();
	Vertice(double x, double y, double z)
	{
		Coor_X = x;
		Coor_Y = y;
		Coor_Z = z;
	}
	~Vertice();
	void MostrarVertice();
	double GetX() { return Coor_X; };
	double GetY() { return Coor_Y; };
	double GetZ() { return Coor_Z; };
	double Memoria();
};


#endif /// !__Vertice__