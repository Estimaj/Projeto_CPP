#ifndef __Face__
#define __Face__


#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <list>
#include <map>
#include "Objetos.h"
#include "Vertice.h"

class Face : public Objetos
{
	///Listas necessarias da Face
	list <int> LInt;
	list <Vertice*> LV;

public:
	Face();
	~Face();
	Face(list <int> Lol, list <Vertice*> VerticeFace);
	void MostrarFace();
	list <Vertice*> Get_ListaVertice() { return LV; }
	list <int> Get_ListaInt() { return LInt; }
	double Comprimento2Vertices(Vertice* V1, Vertice* V2);
	double AreaTriangulo(Vertice* V1, Vertice* V2, Vertice* V3);
	double Area();
	double Memoria();
	bool PontoDentro(Vertice* pb);
	Vertice* IntersetaReta(Vertice* R, Vertice* S);
	Vertice* CalculoVetor(Vertice* V1, Vertice* V2);
	double GetCurvaturadoTriangulo(Vertice* pt1, Vertice* pt2, Vertice* pt3);
};

#endif
