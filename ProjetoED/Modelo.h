#ifndef __Modelo__
#define __Modelo__

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <list>
#include <map>
#include <sstream> 
#include <iomanip>  
#include <vector>
#include "Vertice.h"
#include "Aresta.h"
#include "Face.h"
#include "Objetos.h"
using namespace std;

class Modelo :public Objetos
{
	list <Vertice*> LVertice;
	list <Face*> LFace;
	list <Aresta*> LAresta;


public:
	string nomeModelo;
	double Mem;
	Modelo();
	~Modelo();
	bool Load(const string fich);
	void AddVertice(double x, double y, double z);
	void AddFace(list <int> LV);
	void MostrarListaVertices(list <Vertice*> LV);
	void MostrarListaFaces();
	void MostrarListaArestas(list <Aresta*> LA);
	void AddArestas();
	bool VerificarAresta(Aresta* A);
	double Comprimento2Vertices(Vertice* V1, Vertice* V2);
	double AreaDasFaces();
	Face* AreaMaiorFace();
	double Envolvente();
	double Memoria();
	bool GravarXML(const string& Mfich, const string& XMLpre);
	list <Vertice*> getListaVertice() { return LVertice; }
	list <Aresta*> getListaArestas() { return LAresta; }
	list <Face*> getListaFace() { return LFace; }
	int insideReta(Vertice* A, Vertice* B);
	Face* CurvaturaMaior();
};

#endif
