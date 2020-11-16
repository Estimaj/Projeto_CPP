#ifndef ___SGESTAO__
#define ___SGESTAO__

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <list>
#include <map>
#include "Modelo.h"


using namespace std;

enum Tipo { VERTICE = 0, ARESTA, FACE };  ///Tipos usados na funcao Contar

class SGestao
{
	list <Modelo*> LM; ///Lista de Modelos do sistema de gestao

public:
	SGestao();
	~SGestao();
	bool Load(const string& fich);
	void MostrarMenu();
	void Menu(int op);
	double AreaModelo(const string& fich);
	Face* FaceMaiorArea(const string& fich);
	int Contar(Tipo T);
	double Envolvente(const string& fich);
	double Memoria(const string& nfich);
	Modelo* ModeloMaisMem();
	double MemoriaTotal();
	void MostrarModelos();
	bool GravarXML(const string& Mfich, const string& XMLfich);
	bool RemoverModelo(const string& fich);
	void areaFaceVertice(const string& nfich);
	int insideRetaModelo(const string& nfich);
	Face* FaceMaiorCurvatura(const string& fich);
};

#endif /// ___SGESTAO__


