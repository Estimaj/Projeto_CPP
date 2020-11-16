#ifndef __Aresta__
#define __Aresta__

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <list>
#include <map>
#include <math.h>
#include "Vertice.h"
#include "Objetos.h"

class Aresta : public Objetos
{
	///Vertice da Aresta
	Vertice* V1;
	Vertice* V2;

public:
	Aresta();
	Aresta(Vertice* VertA, Vertice* VertB)
	{
		V1 = VertA;
		V2 = VertB;
	}
	~Aresta();
	void MostrarArestas();
	Vertice* GVert1() { return V1; }
	Vertice* GVert2() { return V2; }
	double Memoria();
};

#endif
