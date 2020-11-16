#include "Aresta.h"



Aresta::Aresta() ///Constructor
{

}


Aresta::~Aresta() ///Destructor
{
}

void Aresta::MostrarArestas()
{
	cout << "Aresta: ";
	V1->MostrarVertice();
	V2->MostrarVertice();
	cout << endl;
}

double Aresta::Memoria()
{
	///Tamanho da Aresta
	return sizeof(Aresta);

}

