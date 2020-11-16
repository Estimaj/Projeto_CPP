#include "Face.h"
#include "Aresta.h"


///Constructor
//-----------------------------------------------------------------------------------------------------------//
Face::Face()
{
}

Face::Face(list <int> LI, list <Vertice*> VerticeFace) ///Usamos uma lista em vez de um conjunto de ints devido ao facto de a face poder ter mais de 3 vertices, n�o obstante o facto de s� usarmos 3 neste exercicio
{
	int x;
	LI.sort();
	for (list<int>::iterator it = LI.begin(); it != LI.end(); ++it)
	{
		x = (*it); /// x fica com o valor atual da lista de ints Lol
		LInt.push_back(x); ///Empurra o valor x para o fim da lista da face
		list<Vertice*>::iterator itV = VerticeFace.begin(); ///Usado para avan�ar a lista de vertices at� � posi��o desejada 
		advance(itV, x - 1); ///x-1 pois a lista come�a na pos 0
		LV.push_back((*itV)); ///Empurra o vertice para a lista de vertices da faces
	}
}

///Destructor//-----------------------------------------------------------------------------------------------------------//

Face::~Face()
{
	///Nao e necessario apagar aqui os vertices pois os vertices pertencem a lista de vertices
	LV.clear();
	LInt.clear();
}

//------------------------------------------------------------------------------------------------------------------------//

void Face::MostrarFace()
{
	cout << endl;
	cout << "Face: ";
	for (list<int>::iterator it = LInt.begin(); it != LInt.end(); ++it) ///iterador da lista de Ints
		cout << " " << (*it) << " "; ///mostra posicao na lista de cada vertice da face
	cout << endl;
	for (list<Vertice*>::iterator Y = LV.begin(); Y != LV.end(); ++Y)
		(*Y)->MostrarVertice();
}

double Face::AreaTriangulo(Vertice* V1, Vertice* V2, Vertice* V3)
{
	double A = Comprimento2Vertices(V1, V2);
	double B = Comprimento2Vertices(V1, V3);
	double C = Comprimento2Vertices(V2, V3);
	double S = (A + B + C) / 2; ///Metade do perimetro

	return sqrt(S * (S - A) * (S - B) * (S - C)); ///Calculo da area do triangulo

}

double Face::Comprimento2Vertices(Vertice* V1, Vertice* V2)
{
	double sx, sy, sz; ///Elementos correspondentes a diferenca entre as coordenadas no calculo da norma
	sx = pow((V1->GetX() - V2->GetX()), 2);
	sy = pow((V1->GetY() - V2->GetY()), 2);
	sz = pow((V1->GetZ() - V2->GetZ()), 2);

	return sqrt(sx + sy + sz);
}

double Face::Area()
{
	int cont = 0;
	double Area = 0;
	Vertice* Aux = NULL;
	for (list<Vertice*>::iterator itv = LV.begin(); itv != LV.end(); ++itv)
	{
		cont++;
		if (cont == 2) Aux = (*itv);
		if (cont >= 3)
		{
			Area += AreaTriangulo(LV.front(), Aux, (*itv));
			Aux = (*itv);
		}
	}
	return Area;
}

double Face::Memoria()
{
	double x = 0;
	x += (LV.size() * sizeof(Vertice));
	x += (LInt.size() * sizeof(int));


	return x;
}

///Funcoes Intersetar Plano//---------------------------------------------------------------------------//

Vertice* Face::CalculoVetor(Vertice* V1, Vertice* V2)
{
	double sx, sy, sz;
	sx = pow((V1->GetX() - V2->GetX()), 2);
	sy = pow((V1->GetY() - V2->GetY()), 2);
	sz = pow((V1->GetZ() - V2->GetZ()), 2);
	Vertice* X = new Vertice(sx, sy, sz);

	return X;

}

Vertice* Face::IntersetaReta(Vertice* R, Vertice* S) ///Obter ponto de intersecao entre reta e plano
{
	int i = 0;
	Vertice* A = NULL;
	Vertice* B = NULL;
	Vertice* C = NULL;

	for (list<Vertice*>::iterator itv = LV.begin(); itv != LV.end(); ++itv)
	{
		i++;
		if (i == 1) {
			A = (*itv);
		}
		else if (i == 2) {
			B = (*itv);
		}
		else if (i == 3) {
			C = (*itv);
		}
	}

	Vertice* AC = CalculoVetor(A, C);
	Vertice* AB = CalculoVetor(A, B);
	///Vertice BA = CalculoVetor(B, A);
	///AC = (a, b,c) e AB = (d, e, f)
	///w1 = (bf - ce), w2 = (cd - af), w3 = (ae - db)

	double w1 = AC->GetY() * AB->GetZ() - AB->GetY() * AC->GetZ();
	double w2 = AC->GetZ() * AB->GetX() - AB->GetZ() * AC->GetX();
	double w3 = AC->GetX() * AB->GetY() - AB->GetX() * AC->GetY();

	double D = w1 * A->GetX() + w2 * A->GetY() + w3 * A->GetZ();
	///Plano = w1*X + w2*Y + w3*Z - D

	Vertice* RS = CalculoVetor(R, S); ///Calculo Vetor da Reta
	double numerador = -(D + w1 * R->GetX() + w2 * R->GetY() + w3 * R->GetZ());
	double denominador = w1 * RS->GetX() + w2 * RS->GetY() + w1 * RS->GetZ();
	if (denominador == 0) { delete AC, AB, RS; return NULL; } ///reta e plano sao paralelos, nao intersetam
	double t = numerador / denominador;

	double Xi = R->GetX() + t * RS->GetX();
	double Yi = R->GetY() + t * RS->GetY();
	double Zi = R->GetZ() + t * RS->GetZ();

	Vertice* I = new Vertice(Xi, Yi, Zi); ///Não esquecer de apagar no fim

	///Eliminar Vetores Criados
	delete AC, AB, RS;

	return I;

}


///Funcoes Intersetar Face//---------------------------------------------------------------------------//

bool Face::PontoDentro(Vertice* I)
{
	if (I == NULL) return false;
	bool Frisk = false;
	int i = 0;
	Vertice* V1 = NULL;
	Vertice* V2 = NULL;
	Vertice* V3 = NULL;
	for (list<Vertice*>::iterator itv = LV.begin(); itv != LV.end(); ++itv)
	{
		i++;
		if (i == 1) {
			V1 = (*itv);
		}
		else if (i == 2) {
			V2 = (*itv);
		}
		else if (i == 3) {
			V3 = (*itv);
		}
	}
	double PBC = AreaTriangulo(I, V2, V3);
	double PAC = AreaTriangulo(V1, V2, I);
	double PAB = AreaTriangulo(V1, I, V3);

	double total = PBC + PAC + PAB;
	double geral = Area();

	if (geral == total)
	{
		cout << endl << "Interseta" << endl;	///printa no ecra
		cout << "Total: " << total << "	 Geral: " << geral << endl;
		Frisk = true;
	}
	return Frisk;
}

double Face::GetCurvaturadoTriangulo(Vertice* pt1, Vertice* pt2, Vertice* pt3)
{
	float Area = AreaTriangulo(pt1, pt2, pt3);
	float Comp1 = Comprimento2Vertices(pt1, pt2); ///Comprimento de pt1 a pt2
	float Comp2 = Comprimento2Vertices(pt2, pt3); ///Comprimento de pt2 a pt3
	float Comp3 = Comprimento2Vertices(pt1, pt3); ///Comprimento de pt1 a pt3
	float Curvatura = 4 * Area / (Comp1 * Comp2 * Comp3);
	return Curvatura;
}