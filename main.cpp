#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::cin;
using std::endl;

typedef struct no
{
	int valor;
	struct no* anterior;
	struct no* proximo;
}no;

void setWindowsUTF8();
int menu(int itens);
int inserirInicio(no** cabeca, no** cauda, int itens);
int inserirFinal(no** cabeca, no** cauda, int itens);
int inserirPosicao(no** cabeca, no** cauda, int itens);
void listarItens(no* cabeca, int itens, bool exibir);
void alterarValor(no** cabeca, no** cauda, int itens);
int excluirPosicao(no** cabeca, no** cauda, int itens);
int limparLista(no** cabeca, no** cauda, int itens);
int obterValor();
int obterPosicao();
bool listaVazia(int itens, bool exibir);
bool validarPosicao(int pos, int itens);

int main()
{
	no* cabeca = NULL;
	no* cauda = NULL;
	int itens = 0;
	bool sair = false;
	
	setWindowsUTF8;

	while (sair == false)
	{
		switch (menu(itens))
		{
		case 1:
			//inserir no inicio
			itens = inserirInicio(&cabeca, &cauda, itens);
			system("cls");
			break;
		case 2:
			//inserir no final
			itens = inserirFinal(&cabeca, &cauda, itens);
			system("cls");
			break;
		case 3:
			//inserir por posição
			listarItens(cabeca, itens, false);
			itens = inserirPosicao(&cabeca, &cauda, itens);
			system("cls");
			break;
		case 4:
			//listar itens
			listarItens(cabeca, itens, true);
			system("cls");
			break;
		case 5:
			//alterar valor por posição
			if (listaVazia(itens, true) == false)
			{
				listarItens(cabeca, itens, false);
				alterarValor(&cabeca, &cauda, itens);
			}
			system("cls");
			break;
		case 6:
			//excluir por posição
			if (listaVazia(itens, true) == false)
			{
				listarItens(cabeca, itens, false);
				itens = excluirPosicao(&cabeca, &cauda, itens);
			}
			system("cls");
			break;
		case 7:
			//limpar lista
			itens = limparLista(&cabeca, &cauda, itens);
			system("cls");
			break;
		case 8:
			//sair
			system("cls");
			cout << "Obrigado por usar! :)" << endl;
			system("pause");
			sair = true;
			break;
		default:
			cout << "ERRO: Opção inválida! :(" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}

int menu(int itens)
{
	int opcao;
	cout << "****LISTA DUPLAMENTE ENCADEADA****" << endl;
	cout << "1 - Inserir no inicio" << endl;
	cout << "2 - Inserir no final" << endl;
	cout << "3 - Inserir por posição" << endl;
	cout << "4 - Listar itens (" << itens << ")" << endl;
	cout << "5 - Alterar valor por posição" << endl;
	cout << "6 - Excluir por posição" << endl;
	cout << "7 - Limpar lista" << endl;
	cout << "8 - Sair" << endl;
	cout << "Escolher: ";
	cin >> opcao;
	return opcao;
}
int inserirInicio(no** cabeca, no** cauda, int itens)
{
	no* novo = (no*) new no;
	int num;

	num = obterValor();
	novo->valor = num;

	if (listaVazia(itens, false) == true)
	{
		novo->proximo = *cauda;
		novo->anterior = NULL;
		*cauda = novo;
		*cabeca = novo;
		itens++;
	}
	else
	{
		novo->proximo = *cabeca;
		novo->anterior = NULL;
		*cabeca = novo;
		(*cabeca)->anterior = novo;
		itens++;
	}
	return itens;
}
int inserirFinal(no** cabeca, no** cauda, int itens)
{
	if (listaVazia(itens, false) == true)
	{
		itens = inserirInicio(&(*cabeca), &(*cauda), itens);
	}
	else
	{
		no* novo = (no*) new no;
		int num;

		num = obterValor();

		novo->valor = num;

		(*cauda)->proximo = novo;
		novo->valor = num;
		novo->proximo = NULL;
		novo->anterior = *cauda;
		*cauda = novo;
		itens++;
	}
	return itens;
}
int inserirPosicao(no** cabeca, no** cauda, int itens)
{
	int pos;
	pos = obterPosicao();
	if (pos >= 1 && pos <= itens + 1)
	{
		if (pos == 1)
		{
			itens = inserirInicio(&(*cabeca), &(*cauda), itens);
			return itens;
		}
		else
		{
			if (pos == itens + 1)
			{
				itens = inserirFinal(&(*cabeca), &(*cauda), itens);
				return itens;
			}
			else
			{
				no* aux = *cabeca;
				no* aux2;
				no* novo = (no*) new no;
				int num;

				num = obterValor();
				
				novo->valor = num;

				for (int i = 1; i < pos; i++)
				{
					aux = aux->proximo;
				}
				aux2 = aux;
				aux = aux->anterior;
				novo->proximo = aux2;
				aux->proximo = novo;
				aux2->anterior = novo;
				itens++;
				return itens;
			}
		}

	}
	else
	{
		validarPosicao(pos, itens);
		return itens;
	}
}
void listarItens(no* cabeca, int itens, bool exibir)
{
	no* aux = cabeca;
	if (listaVazia(itens, exibir) == true)
	{
	}
	else
	{
		int pos = 1;
		while (aux != NULL)
		{
			cout << pos << "ª :" << aux->valor << endl;
			aux = aux->proximo;
			pos++;
		}
		if (exibir == true)
		{
			system("pause");
		}
	}
}
void alterarValor(no** cabeca, no** cauda, int itens)
{
	int pos;
	pos = obterPosicao();
	if (validarPosicao(pos, itens) == true)
	{
		int num;
		num = obterValor();
		if (pos == 1)
		{
			(*cabeca)->valor = num;
		}
		else
		{
			if (pos == itens)
			{
				(*cauda)->valor = num;
			}
			else
			{
				no* aux = *cabeca;
				for (int i = 1; i < pos; i++)
				{
					aux = aux->proximo;
				}
				aux->valor = num;
			}
		}
	}
	else
	{
	}
}
int excluirPosicao(no** cabeca, no** cauda, int itens)
{
	int pos;
	pos = obterPosicao();
	if (validarPosicao(pos, itens) == true)
	{
		no* aux;
		if (pos == 1)
		{
			if (itens > 1)
			{
				aux = (*cabeca)->proximo;
				delete aux->anterior;
				aux->anterior = NULL;
				*cabeca = aux;
			}
			else
			{
				delete* cabeca;
				*cabeca = NULL;
				*cauda = NULL;
			}
		}
		else
		{
			if (pos == itens)
			{
				aux = (*cauda)->anterior;
				delete aux->proximo;
				aux->proximo = NULL;
				*cauda = aux;
			}
			else
			{
				aux = *cabeca;
				no* aux2;
				no* aux3;
				for (int i = 1; i < pos; i++)
				{
					aux = aux->proximo;
				}
				aux2 = aux;
				aux3 = aux->proximo;
				aux = aux->anterior;
				delete aux2;
				aux->proximo = aux3;
				aux3->anterior = aux;
			}
		}
		itens--;
	}
	return itens;
}
int limparLista(no** cabeca, no** cauda, int itens)
{
	if (listaVazia(itens, true) == true)
	{
	}
	else
	{
		no* aux = *cabeca;
		no* aux2;
		while (aux != NULL)
		{
			aux2 = aux;
			aux = aux->proximo;
			delete aux2;
		}
		*cabeca = NULL;
		*cauda = NULL;
		itens = 0;
	}
	return itens;
}
int obterValor()
{
	int num;
	cout << "Entre com um valor inteiro: ";
	cin >> num;
	return num;
}
int obterPosicao()
{
	int pos;
	cout << "Entre com uma posição: ";
	cin >> pos;
	return pos;
}
bool listaVazia(int itens, bool exibir)
{
	if (itens == 0)
	{
		if (exibir == true)
		{
			cout << "ERRO: Lista vazia!" << endl;
			system("pause");
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool validarPosicao(int pos, int itens)
{
	if (itens != 0 && pos >= 1 && pos <= itens)
	{
		return true;
	}
	else
	{
		cout << "ERRO: Posição inválida!" << endl;
		system("pause");
		return false;
	}
}
void setWindowsUTF8()
{
	system("chcp 65001");
	system("cls");
}
