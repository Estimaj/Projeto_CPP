#include "Modelo.h"


Modelo::Modelo() ///Constructor Modelo
{
	Mem = 0;
}


Modelo::~Modelo() ///Destructor Modelo
{
	cout << "Passei em <" << __FUNCTION__ << ">" << endl;


	if (LFace.size() > 0) ///Pre-Check para evitar desperdicio recursos
	{
		for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it) ///iterador da lista de Faces
		{
			delete(*it);
		}
	}

	if (LAresta.size() > 0) ///Pre-Check para evitar desperdicio recursos
	{
		for (list<Aresta*>::iterator it = LAresta.begin(); it != LAresta.end(); ++it) ///iterador da lista de Arestas
		{
			delete(*it);
		}

	}

	if (LVertice.size() > 0) ///Pre-Check para evitar desperdicio recursos
	{
		for (list<Vertice*>::iterator it = LVertice.begin(); it != LVertice.end(); ++it) ///iterador da lista de Vertices
		{
			delete(*it);
		}
	}

	///Limpar Listas após libertacao de objetos
	cout << "Aresta:  " << LAresta.size() << " Vertice: " << LVertice.size() << " Face: " << LFace.size() << endl;
	LAresta.clear();
	LVertice.clear();
	LFace.clear();
	cout << "Aresta:  " << LAresta.size() << " Vertice: " << LVertice.size() << " Face: " << LFace.size() << endl;


}

//----------------------------------------------------------------------------------------------------------------//

bool Modelo::GravarXML(const string& Mfich, const string& XMLpre) ///Gravar Modelo em formato XML
{
	///Inicializacao de variaveis
	ofstream Fich;
	string XMLfich;
	XMLfich = XMLpre + ".xml"; ///Garante que o ficheiro e xml

	///Abertura de ficheiro XML para escrita
	Fich.open(XMLfich.c_str(), ofstream::out);

	if (LVertice.size() == 0) Fich << "O Ficheiro nao possui vertices" << endl; ///Pre-Check para evitar desperdicio recursos
	else {
		for (list<Vertice*>::iterator it = LVertice.begin(); it != LVertice.end(); ++it)
			Fich << "vertice: " << (*it)->GetX() << " " << (*it)->GetY() << " " << (*it)->GetZ() << endl;
	}

	if (LFace.size() == 0) Fich << "O Ficheiro nao possui faces" << endl; ///Pre-Check para evitar desperdicio recursos
	else {
		for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it)
		{
			list<int> INT = (*it)->Get_ListaInt();
			Fich << "face: ";
			for (list<int>::iterator itv = INT.begin(); itv != INT.end(); ++itv)
				Fich << (*itv) << " ";
			Fich << endl;

		}
	}
	Fich.close(); ///Fechar ficheiro
	return true;
}

double Modelo::Comprimento2Vertices(Vertice* V1, Vertice* V2)
{
	///Calculo de elementos correspondentes a diferenca entre as coordenadas no calculo da norma
	double sx, sy, sz;
	sx = pow((V1->GetX() - V2->GetX()), 2);
	sy = pow((V1->GetY() - V2->GetY()), 2);
	sz = pow((V1->GetZ() - V2->GetZ()), 2);

	///Calculo e retorno da norma
	return sqrt(sx + sy + sz);
}

int Modelo::insideReta(Vertice* A, Vertice* B) ///Dados os vetores da Reta
{


	///Pre-check para evitar desperdicio de recursos
	if (LFace.size() == 0) { cout << "Lista Vazia (Faces)!" << endl; return -1; }

	///Inicializar Variaveis
	int Qt = 0;
	Vertice* I = NULL;

	///Verificar quantidade de intersecoes
	for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it)
	{
		I = (*it)->IntersetaReta(A, B);
		if ((*it)->PontoDentro(I)) Qt++;
	}
	delete I;

	///Retorna numero intersecoes
	return Qt;
}

///Funcoes para Mostrar Listas
//---------------------------------------------------------------------------------//

void Modelo::MostrarListaVertices(list <Vertice*> LV)
{
	cout << "Passei em <" << __FUNCTION__ << ">" << endl;
	if (LV.size() == 0) { cout << "Lista Vazia (Faces)!" << endl; return; }
	for (list<Vertice*>::iterator it = LV.begin(); it != LV.end(); ++it)
		(*it)->MostrarVertice();

}

void Modelo::MostrarListaFaces()
{
	cout << "Passei em <" << __FUNCTION__ << ">" << endl;
	if (LFace.size() == 0) { cout << "Lista Vazia (Faces)!" << endl; return; }
	for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it)
		(*it)->MostrarFace();
}

void Modelo::MostrarListaArestas(list <Aresta*> LA)
{
	cout << "Passei em <" << __FUNCTION__ << ">" << endl;
	if (LA.size() == 0) { cout << "Lista Vazia (Arestas)!" << endl; return; }
	for (list<Aresta*>::iterator it = LA.begin(); it != LA.end(); ++it)
		(*it)->MostrarArestas();

}

///Funcoes para Adicionar Elementos
//---------------------------------------------------------------------------------//

void Modelo::AddVertice(double x, double y, double z)
{
	///cout << "Passei em <" << __FUNCTION__ << ">" << endl;
	Vertice* Vert = new Vertice(x, y, z); ///Cria um vertice novo 
	LVertice.push_back(Vert); ///Empurra o Vertice para o fim da Lista


}

void Modelo::AddFace(list <int> LV)
{
	//cout << "Passei em <" << __FUNCTION__ << ">" << endl;
	Face* Fac = new Face(LV, LVertice); ///Cria uma face nova
	LFace.push_back(Fac); ///Empurra a face para o fim da Lista

}


void Modelo::AddArestas() ///O objetivo seria no fim de fazer o loading das faces e vertices, calcular as arestas
{
	///Inicializar Variaveis
	Vertice* aux = NULL;
	int cont = 0;

	///Para cada face do Modelo, verificar cada face
	for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it) ///Percorre a lista de faces
	{
		list <Vertice*> X = (*it)->Get_ListaVertice(); ///Lista Vertices da face
		for (list<Vertice*>::iterator itv = X.begin(); itv != X.end(); ++itv)
		{
			Aresta* A; ///Aresta auxiliar

			///Se a Aresta atual for a primeira, entao liga-se a ultima, como um ouroboros
			if ((*itv) == X.front()) A = new Aresta((*itv), X.back());
			else A = new Aresta(aux, (*itv));

			///Se o verificar for true, a aresta e unica e colocada na lista
			if (VerificarAresta(A)) LAresta.push_back(A);
			///Caso contrario, e apagada
			else delete A;

			///Auxiliar passa a ser o elemento atual
			aux = (*itv);
		}
	}
}

///Funcoes para verificar unicidade de arestas
//-----------------------------------------------------------------------//

bool CompararArestas(Aresta* A, Aresta* B)
{
	///Verificar se as arestas sao iguais
	return ((A->GVert1() == B->GVert2()) && (A->GVert2() == B->GVert1())) ||
		((A->GVert1() == B->GVert1()) && (A->GVert2() == B->GVert2()));
}

bool Modelo::VerificarAresta(Aresta* A)
{
	for (list<Aresta*>::iterator it = LAresta.begin(); it != LAresta.end(); ++it)
	{
		if (CompararArestas(A, (*it))) return false;
	}
	return true;
}

///Funcoes de Areas
//-------------------------------------------------------------------------------------------//

double Modelo::AreaDasFaces()
{
	///Inicializar Variaveis
	double AreaTotal = 0;

	///Pre-Check para evitar desperdicio recursos
	if (LFace.size() == 0) { cout << "Lista Vazia (Faces)!" << endl; return AreaTotal; }

	///Calculo da area Total
	for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it)
	{
		AreaTotal += (*it)->Area();
	}
	return AreaTotal;
}

Face* Modelo::AreaMaiorFace()
{
	///Inicializar Variaveis
	Face* F = NULL;
	double AreaTotal = 0;
	double Aux = 0;

	///Pre-check para evitar desperdicio recursos
	if (LFace.size() == 0) { cout << "Lista Vazia (Faces)!" << endl; return F; }

	///Comparacao entre Face maxima atual e "pretendente ao trono"
	for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it)
	{
		Aux = (*it)->Area();
		if (AreaTotal <= Aux)
		{
			///Troca recorrendo a Auxiliar
			AreaTotal = Aux;
			F = (*it);
		}
	}
	return F;

}



Face* Modelo::CurvaturaMaior()
{
	///Inicializar Variaveis
	Vertice* V1 = NULL;
	Vertice* V2 = NULL;
	Vertice* V3 = NULL;


	double x = 0;
	double aux = 0;

	Face* bigger=NULL;
	///Pre-check para evitar desperdicio recursos
	if (LFace.size() == 0) { cout << "Lista Vazia (Faces)!" << endl; return NULL; }

	///Comparacao entre Face maxima atual e "pretendente ao trono"
	for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it)
	{
		list <Vertice*> X = (*it)->Get_ListaVertice();
		for (list<Vertice*>::iterator itv = X.begin(); itv != X.end(); ++itv)
		{
			if (X.size() == 3) {
				V1 = (*itv);
				++itv;
				V2 = (*itv);
				++itv;
				V3 = (*itv);
			}
			else {
				printf("Aqui esta o erro n tem 3 de tamanho\n");
			}
		}
		x = (*it)->GetCurvaturadoTriangulo(V1,V2,V3);

		///Comparar Curvaturas
		if (x > aux) {
			aux = x;
			bigger = (*it);
		}
	}
	return bigger;
}


double Modelo::Envolvente()
{
	///Pre-check para evitar desperdicio de recursos
	if (LVertice.size() == 0) { cout << "Lista Vazia" << endl; return -1; }

	///Inicializar Variaveis
	Vertice* Pmin, * Pmax, * P1, * P2;
	double zmax = LVertice.front()->GetZ(),
		zmin = LVertice.front()->GetZ(),
		xmax = LVertice.front()->GetX(),
		xmin = LVertice.front()->GetX(),
		ymax = LVertice.front()->GetY(),
		ymin = LVertice.front()->GetY();

	///Calculo do ponto Max e ponto Min
	for (list<Vertice*>::iterator itv = LVertice.begin(); itv != LVertice.end(); ++itv)
	{
		if (xmax <= (*itv)->GetX()) xmax = (*itv)->GetX();
		if (ymax <= (*itv)->GetY()) ymax = (*itv)->GetY();
		if (zmax <= (*itv)->GetZ()) zmax = (*itv)->GetZ();
		if (xmin >= (*itv)->GetX()) xmin = (*itv)->GetX();
		if (ymin >= (*itv)->GetY()) ymin = (*itv)->GetY();
		if (zmin >= (*itv)->GetZ()) zmin = (*itv)->GetZ();

	}

	///Criacao dos 4 pontos necessarios
	Pmax = new Vertice(xmax, ymax, zmax); ///Ponto maximo
	Pmin = new Vertice(xmin, ymin, zmin); ///Ponto minimo
	P1 = new Vertice(xmax, ymax, zmin); ///Ponto Aux 1
	P2 = new Vertice(xmin, ymax, zmin); ///Ponto Aux 2

	///Calculo do Envolvente
	double Lado1 = Comprimento2Vertices(P1, Pmax),
		Lado2 = Comprimento2Vertices(P2, Pmin),
		Lado3 = Comprimento2Vertices(P1, P2),
		Resultado = (2 * Lado1 * Lado2 + 2 * Lado2 * Lado3 + 2 * Lado3 * Lado1);

	///Eliminacao dos Pontos
	delete Pmax, Pmin, P1, P2;

	return Resultado;
}

//-------------------------------------------------------------------------------------------------------------------//

double Modelo::Memoria()
{
	///Funcao chama a Funcao de Memoria de todos os outros objetos
	double Memoria = 0;
	for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it)
	{
		Memoria += (*it)->Memoria();
	}
	for (list<Vertice*>::iterator it = LVertice.begin(); it != LVertice.end(); ++it)
	{
		Memoria += (*it)->Memoria();
	}
	for (list<Aresta*>::iterator it = LAresta.begin(); it != LAresta.end(); ++it)
	{
		Memoria += (*it)->Memoria();
	}
	///Memoria anterior + especificos do Modelo
	return Memoria + sizeof(string) + sizeof(double);
}


//---------------------------------------------------------------------------------------------------------------------//


bool Modelo::Load(const string fich)
{
	///Abertura do Ficheiro
	ifstream F(fich.c_str());
	if (!F) return 0;

	///Inicializar Variaveis
	double vx, vy, vz;
	int cont = 0, X = 0;
	string str;

	///Leitura do Ficheiro
	while (!F.eof()) {

		getline(F, str); ///Leitura linha a linha
		stringstream ss(str);

		///Se for Vertice
		if (str[0] == 'v') {

			ss.ignore(256, ' ');
			ss >> vx, ss >> vy, ss >> vz;
			AddVertice(vx, vy, vz);

		}
		///Se for Face
		if (str[0] == 'f') {


			list <int> LInt;
			ss.ignore(256, ' ');
			while (ss >> X) LInt.push_back(X);

			AddFace(LInt);
		}
	}
	///Calculo das Arestas
	AddArestas();

	///Informacao utilitaria
	cout << endl << "-----------------------------" << endl;
	cout << "Numero Arestas: " << LAresta.size() << endl;
	cout << "Numero Faces: " << LFace.size() << endl;
	cout << "Numero Vertices: " << LVertice.size() << endl;
	cout << "-----------------------------" << endl;

	F.close(); ///Fecha o ficheiro

	return 1; ///true
}

