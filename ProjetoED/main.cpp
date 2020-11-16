#include "SGestao.h"


int main()
{
	char op[] = "10"; /// Inicializar op
	int opc = -2; /// inicializar opc

	cout << "Se desejar ir para o menu use uma das opcoes propostas, caso deseje testar memoria digite -1!" << endl;
	SGestao* DS = new SGestao(); /// Criar o sistema de gest�o
	while (opc != 0 && opc != -1) ///Enquanto OPC n�o for 0, o programa repete
	{
		DS->MostrarMenu(); ///Mostra o Menu Principal, incluindo os modelos em mem�ria
		cout << "Opcao: ";
		cin >> op;
		if (isdigit(op[0])) { ///Verifica se op � digito
			opc = atoi(op); ///Passagem de char op para opc
		}
		else { cout << endl << "Coloque um valor valido" << endl; opc = -1; }
		DS->Menu(opc); ///Vai para o switch da opcao escolhida

	}
	

	///Testa a memoria na opcao -1
	cout << "Objeto a testar: ";
	cin >> op;
	while (opc == -1)
	{
		SGestao* DS = new SGestao();
		DS->Load(op);
		delete DS;
	}
	delete DS; ///Chama o destructor para fechar o programa
}
