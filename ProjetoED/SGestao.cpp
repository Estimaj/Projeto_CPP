#include "SGestao.h"



SGestao::SGestao() ///Constructor
{


}


SGestao::~SGestao() ///Destructor
{
	//cout << "Passei em <" << __FUNCTION__ << ">" << endl;
	while (LM.size() != 0) ///Enquanto existirem Modelos
	{
		delete LM.front(); ///Apaga o contéudo do Modelo da frente
		LM.pop_front(); ///Faz pop do primeiro elemento, ja vazio

	}
	cout << "Modelos:  " << LM.size() << endl;
	LM.clear(); ///Ter a certeza que a Lista está mesmo vazia
}


bool SGestao::Load(const string& fich)
{
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it) ///Verificar se ja existe o ficheiro em memoria
	{
		if ((*it)->nomeModelo == fich)
		{
			cout << "Ficheiro ja em memoria" << endl;
			return false;
		}
	}
	Modelo* M = new Modelo(); ///Novo Modelo
	bool Res = M->Load(fich); ///Fazer Load do ficheiro objeto para o Modelo
	if (Res == 1) ///Caso o Load seja bem sucedido
	{
		M->nomeModelo = fich; ///Nome do modelo passa a ser o do ficheiro
		LM.push_back(M); ///Modelo empurrado para o fim da lista
		return true;
	}
	else { ///Caso o Load NAO seja bem sucedido
		cout << "Erro no load do ficheiro" << endl;
		delete M; ///Destruir modelo nao utilizado
	}
	return false;


}

bool SGestao::GravarXML(const string& Mfich, const string& XMLfich) ///Gravar ficheiro em formato Xml
{
	Modelo* M = NULL; ///Inicializar Modelo de auxilio

	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it) ///Verificar se o modelo a gravar existe em memoria
	{
		if ((*it)->nomeModelo == Mfich) ///Se modelo for encontrado
		{
			M = (*it); ///Modelo Temp e igual ao encontrado
			M->GravarXML(Mfich, XMLfich); ///O ficheiro XML e gravado com o nome especificado
		}
	}
	if (M == NULL) { ///Se modelo nao for encontrado
		cout << "Nao existe ficheiro com esse nome" << endl;
		return false;
	}
	return true;
}

bool SGestao::RemoverModelo(const string& fich)
{
	cout << "LM SIZE: " << LM.size() << endl;
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it) ///Verificar se o modelo a remover esta em memoria
	{
		if ((*it)->nomeModelo == fich) ///Se o modelo a remover for encontrado
		{
			delete(*it); ///Apaga Conteudo do modelo
			LM.erase(it); ///Apaga posicao na lista do modelo
			cout << endl << "Modelo " << fich << " Removido com sucesso!" << endl;
			cout << "LM SIZE: " << LM.size() << endl;


			return true;
		}
	}
	cout << endl << "Modelo " << fich << " Nao existe!" << endl; ///Caso nao haja modelo com nome colocado
	return false;
}

double SGestao::AreaModelo(const string& fich) ///Area do Modelo ///Funcao a incluir no Objeto
{
	Modelo* M = NULL; ///Modelo temporario
	double Area = 0; ///Inicializar a variavel area
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it) ///Verificar se o Modelo existe
	{
		if ((*it)->nomeModelo == fich) ///Caso exista o modelo
		{
			M = (*it); ///Modelo temp e igual ao encontrado
			Area = M->AreaDasFaces(); ///Calculo da area do Modelo
			break;
		}
	}
	if (M == NULL) cout << "Nao existe ficheiro com esse nome" << endl; ///Caso nao exista modelo
	
	return Area; ///Retorna double Area a Sgestao

}


double SGestao::Envolvente(const string& fich) //Calculo do Paralelipipedo envolvente do Modelo
{
	Modelo* M = NULL; ///Inicializar Modelo Temp
	double x = 0; ///Inicializar Double
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it) ///Verificar se Modelo existe
	{
		if ((*it)->nomeModelo == fich) ///Se for encontrado
		{
			M = (*it); ///Modelo Temp igual a encontrado
			break;
		}
	}
	if (M == NULL) { cout << "Nao existe ficheiro com esse nome" << endl; return -1; } ///Caso nao encontre
	x = M->Envolvente(); ///Calculo do Envolvente
	return x; ///Retorna a area do envolvente

}



int SGestao::Contar(Tipo T) { ///Contador de Vertice/Face/Aresta
	int contador = 0;
	switch (T)
	{
	case VERTICE: contador++; break;
	case ARESTA: contador++; break;
	case FACE: contador++; break;
	default: cout << "Objeto n conhecido" << endl; contador = -1; break;
	}
	return contador; ///Retorna valor contador
}

void SGestao::areaFaceVertice(const string& nfich) {
	Modelo* M = NULL; ///Inicializa Modelo Temp
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it) ///Verifica se existe modelo
	{
		if ((*it)->nomeModelo == nfich) ///Caso encontre modelo
		{
			M = (*it); ///Modelo Temp e igual a encontrado
			break;
		}
	}
	if (M == NULL) { cout << "Nao existe ficheiro com esse nome" << endl; return; } ///Caso nao encontre modelo

	///Obter Listas do Modelo
	list <Vertice*> LVertice = M->getListaVertice();
	list <Aresta*> LAresta = M->getListaArestas();
	list <Face*> LFace = M->getListaFace();

	///Iterador para obter numero de Arestas/Faces/Vertices
	int cVertice = 0, cFace = 0, cAresta = 0;
	for (list<Face*>::iterator it = LFace.begin(); it != LFace.end(); ++it) {
		cFace += Contar(FACE);
	}
	for (list<Vertice*>::iterator it = LVertice.begin(); it != LVertice.end(); ++it) {
		cVertice += Contar(VERTICE);
	}
	for (list<Aresta*>::iterator it = LAresta.begin(); it != LAresta.end(); ++it) {
		cAresta += Contar(ARESTA);
	}

	///Resultado
	cout << "Faces:" << cFace << endl;
	cout << "Vertices:" << cVertice << endl;
	cout << "Arestas:" << cAresta << endl;
}

int SGestao::insideRetaModelo(const string& nfich) ///Numero de faces perfuradas por uma reta
{
	///Inicializar Variaveis
	Modelo* M = NULL;
	float ax = 0, ay = 0, az = 0, bx = 0, by = 0, bz = 0;
	int ok = 0;

	///Verificar se Modelo existe em memoria
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		if ((*it)->nomeModelo == nfich)
		{
			M = (*it);
			break;
		}
	}
	if (M == NULL) { cout << "Nao existe ficheiro com esse nome" << endl; return -1; }

	///Coordenadas do ponto ///Provavelmente vai ser alterado para ponto de interseçao da reta com face
	cout << "Coordenadas do Ponto A da Reta: " << endl;
	cout << "X: ";
	cin >> ax;
	cout << endl << "Y: ";
	cin >> ay;
	cout << endl << "Z: ";
	cin >> az;

	cout << "Coordenadas do Ponto B da Reta: " << endl;
	cout << "X: ";
	cin >> bx;
	cout << endl << "Y: ";
	cin >> by;
	cout << endl << "Z: ";
	cin >> bz;

	Vertice* A = new Vertice(ax, ay, az);
	Vertice* B = new Vertice(bx, by, bz);

	///Calculo de intersecoes com faces
	ok = M->insideReta(A, B);

	delete A, B;

	return ok;
}

double SGestao::Memoria(const string& nfich)
{
	///Inicializar Variaveis
	Modelo* M = NULL;
	double x = 0;

	///Verificar se Modelo existe
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		if ((*it)->nomeModelo == nfich)
		{
			M = (*it);
			break;
		}
	}
	if (M == NULL) { cout << "Nao existe ficheiro com esse nome" << endl; return -1; }

	///Calculo da Memoria
	x = M->Memoria();
	return x;
}

double SGestao::MemoriaTotal()
{
	///Pre-Check para nao gastar mais recursos que necessario
	if (LM.size() == 0) { cout << "Nao existem Modelos" << endl; return 0; }

	///Inicializar Variaveis
	double MaxMem = 0;

	///Calculo da Memoria Total
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		if ((*it)->Mem == 0) ///Se Modelo ainda nao tiver a memoria calculada anteriormente
			(*it)->Mem = (*it)->Memoria();
		MaxMem += (*it)->Mem;
	}

	///Retornar Memoria Total
	return MaxMem;
}

Modelo* SGestao::ModeloMaisMem()
{
	///Pre-Check para nao gastar mais recursos que necessario
	if (LM.size() == 0) { cout << "Nao existem Modelos" << endl; return NULL; }

	///Inicializar Variaveis
	Modelo* M = LM.front();
	double MaxMem = M->Memoria();

	///Ver qual o modelo com mais memoria
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		///Se o Modelo ainda nao tiver memoria calculada
		if ((*it)->Mem == 0)
			(*it)->Mem = (*it)->Memoria();
		///Comparacao entre Modelo maximo atual e "pretendente ao trono"
		if ((*it)->Mem > MaxMem)
		{
			M = (*it);
			MaxMem = (*it)->Mem;
			break;
		}
	}
	///Retorna Modelo com maior memoria
	return M;
}


void SGestao::MostrarModelos() ///Mostrar todos os modelos do SGestao
{
	cout << "Quantidade de Modelos em Memoria: " << LM.size() << endl;

	///Precheck para nao gastar recursos a mais
	if (LM.size() == 0) { cout << "Ainda nao tem Modelos em Memoria" << endl; return; }

	///Inicializar Variaveis
	int index = 0;

	///Mostrar cada Modelo: Inclui nomeModelo e Memoria Ocupada
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		index++; ///Usado para efeitos de lista numerica
		if ((*it)->Mem <= 0) (*it)->Mem = (*it)->Memoria();
		cout << index << ". " << (*it)->nomeModelo << " Memoria Ocupada:" << (*it)->Mem << endl;
	}
}

Face* SGestao::FaceMaiorArea(const string& fich) ///Obter Face do Modelo com maior area
{
	Modelo* M = NULL; ///Inicializar Modelo Temp
	Face* F = NULL; ///Inicializar Face Temp
	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it) ///Verificar se Modelo existe em memoria
	{
		if ((*it)->nomeModelo == fich) ///Caso Modelo exista
		{
			M = (*it); ///Modelo Temp e igual a encontrado
			break;
		}
	}
	F = M->AreaMaiorFace(); ///A funcao coloca em F a Face maior
	if (M == NULL) cout << "Nao existe ficheiro com esse nome" << endl; ///Caso nao esteja Modelo em memoria
	return F; ///retorna a Funcao com maior face ou NULL
}

Face* SGestao::FaceMaiorCurvatura(const string& fich) {
	///Pre-Check para nao gastar mais recursos que necessario
	if (LM.size() == 0) { cout << "Nao existem Modelos" << endl; return NULL; }

	///Inicializar Variaveis
	Modelo* M = LM.front();
	Face* F = NULL; ///Inicializar Face Temp

	for (list<Modelo*>::iterator it = LM.begin(); it != LM.end(); ++it)
	{
		if ((*it)->nomeModelo == fich) ///Caso Modelo exista
		{
			M = (*it); ///Modelo Temp e igual a encontrado
			break;
		}
	}
	F = M->CurvaturaMaior(); ///A funcao coloca em F a Face maior
	if (M == NULL) cout << "Nao existe ficheiro com esse nome" << endl; ///Caso nao esteja Modelo em memoria
	return F; ///retorna a Funcao com maior face ou NULL
}

void SGestao::MostrarMenu()
{
	cout << endl;
	cout << "------------------Menu-------------------" << endl;
	cout << "-----------------Opcoes------------------" << endl;
	cout << "0. Sair" << endl;
	cout << "1. Load de um Modelo" << endl;
	cout << "2. Area de um Modelo" << endl;
	cout << "3. Numero de Arestas, Vertices e Faces" << endl;
	cout << "4. Envolvente de um Modelo" << endl;
	cout << "5. Memoria ocupada por um modelo" << endl;
	cout << "6. Modelo que ocupa mais memoria" << endl;
	cout << "7. Memoria Total Ocupada" << endl;
	cout << "8. Numero Faces de um Modelo atravessadas por uma reta" << endl;
	cout << "9. Face de modelo com maior area" << endl;
	cout << "10. Remover um modelo" << endl;
	cout << "11. Gravar Modelo em XML" << endl;
	cout << "12. Curvatura Face de Modelo" << endl;
	cout << "13. Loop" << endl;

	cout << "----------------------------------------" << endl;
	cout << endl;
	cout << "-----------Modelos em Memoria-----------" << endl;
	MostrarModelos(); ///Mostra todos os modelos em memoria
	cout << "----------------------------------------" << endl;
	cout << endl;



}

void SGestao::Menu(int op)
{
	///Estrutura Basica: Pedir nome do ficheiro(s) a utilizar e demontracao de resultados
	///13 casos, nao incluindo default e sair
	switch (op)
	{
	case 0: cout << "Programa vai desligar" << endl;  break;

	case 1:
	{
		cout << endl;
		string nfich;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro? " << endl;
		cout << "Ficheiro: ";
		cin >> nfich;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		Load(nfich);
		cout << endl;
		break;
	}
	case 2:
	{
		cout << endl;
		string nfich;
		double x = 0;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro? " << endl;
		cout << "Ficheiro: ";
		cin >> nfich;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		x = AreaModelo(nfich);
		cout << endl << "-----------------------------" << endl;
		cout << "Area do Modelo: " << x << endl;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		break;
	}

	case 3:
	{
		cout << endl;
		string nfich;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro? " << endl;
		cout << "Ficheiro: ";
		cin >> nfich;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		cout << endl << "-----------------------------" << endl;
		areaFaceVertice(nfich);
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		break;
	}

	case 4:
	{
		cout << endl;
		string nfich, op;
		double x = 0;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro? " << endl;
		cout << "Ficheiro: ";
		cin >> nfich;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		x = Envolvente(nfich);
		cout << endl << "-----------------------------" << endl;
		cout << "Envolvente do Modelo: " << x << endl;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		break;
	}

	case 5:
	{
		cout << endl;
		string nfich, op;
		double x = 0;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro? " << endl;
		cout << "Ficheiro: ";
		cin >> nfich;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		x = Memoria(nfich);
		cout << endl << "-----------------------------" << endl;
		cout << "Memoria Ocupada pelo Modelo: " << x << endl;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		break;
	}

	case 6:
	{
		cout << endl;
		Modelo* M = ModeloMaisMem();
		cout << endl << "-----------------------------" << endl;
		cout << "Nome Modelo que ocupa mais: " << M->nomeModelo << endl;
		cout << "Memoria Ocupada pelo Modelo: " << M->Mem << endl;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		break;
	}

	case 7:
	{
		cout << endl;
		double x = 0;
		x = MemoriaTotal();
		cout << endl << "-----------------------------" << endl;
		cout << "Memoria Total Ocupada: " << x << endl;
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		break;
	}

	case 8: {
		cout << endl;
		int x = 0;
		string nfich;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro? " << endl;
		cout << "Ficheiro: ";
		cin >> nfich;
		cout << endl << "-----------------------------" << endl;
		x = insideRetaModelo(nfich);
		cout << "Interseta " << x << " vezes" << endl;
		break;
	}
	case 9:
	{
		cout << endl;
		string nfich;
		Face* F = NULL;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro? " << endl;
		cout << "Ficheiro: ";
		cin >> nfich;
		cout << endl << "-----------------------------" << endl;
		F = FaceMaiorArea(nfich);
		cout << endl << "-----------------------------" << endl;
		F->MostrarFace();
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		break;
	}

	case 10: {
		cout << endl;
		string nfich;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro? " << endl;
		cout << "Ficheiro: ";
		cin >> nfich;
		cout << endl << "-----------------------------" << endl;
		RemoverModelo(nfich);
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		break;
	}

	case 11:
	{
		cout << endl;
		string mfich, xmlfich;
		bool x = false;
		Face* F = NULL;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro Modelo? " << endl;
		cout << "Ficheiro: ";
		cin >> mfich;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro XML? " << endl;
		cout << "Ficheiro: ";
		cin >> xmlfich;
		cout << endl << "-----------------------------" << endl;
		x = GravarXML(mfich, xmlfich);
		if (x == true) cout << "Sucesso" << endl;
		else cout << "Insucesso" << endl;
	}
	case 12: {
		cout << endl;
		string mfich;
		Face* F = NULL;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro Modelo? " << endl;
		cout << "Ficheiro: ";
		cin >> mfich;
		cout << endl << "-----------------------------" << endl;
		F = FaceMaiorCurvatura(mfich);
		cout << endl << "-----------------------------" << endl;
		F->MostrarFace();
		cout << endl << "-----------------------------" << endl;
		cout << endl;
		break;
	}
	case 13:
	{
		cout << endl;
		string mfich;
		cout << endl << "-----------------------------" << endl;
		cout << "Qual o nome do ficheiro Modelo? " << endl;
		cout << "Ficheiro: ";
		cin >> mfich;
		cout << endl << "-----------------------------" << endl;
		while (1)
		{
			Load(mfich);
			RemoverModelo(mfich);

		}
	}
	default: cout << "Opcao nao existe!" << endl; break;
	}

}