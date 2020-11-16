#include "Vertice.h"



Vertice::Vertice() ///Constructor 
{
	Coor_X = 0;
	Coor_Y = 0;
	Coor_Z = 0;
}


Vertice::~Vertice() ///Destructor
{
}

void Vertice::MostrarVertice()
{
	cout << "Vertice: ";
	cout << " X: " << Coor_X << " Y: " << Coor_Y << " Z: " << Coor_Z << endl;

}

double Vertice::Memoria()
{
	///Tamanho dos 3 doubles do Vertice
	return (3 * sizeof(double));
}