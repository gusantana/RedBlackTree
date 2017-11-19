/*Trabalho Estrutura de Dados 2
Universidade Federal do Mato Grosso
Instituto de Ciências Exatas e da Terra
Ciência da Computação

Docente: Luciana Lee

Grupo 4:
	Gustavo Santana Coelho;
	Guilherme Santana Coelho;
	Vitor Rezende Campos.

Exercício 2.
1º Arquivo Header
*/
#ifndef __Arvore_Rubro_Negra__
#define __Arvore_Rubro_Negra__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Tipo de propriedade:
#define IMOVEL 1
#define TERRENO 2

//Objetivo:
#define VENDA 1
#define LOCACAO 2

//Disponibilidade (Locação apenas)
#define INDISPONIVEL 1
#define DISPONIVEL 2

//Cor do nó:
#define RUBRO 1
#define Rubro 1

#define NEGRO 0
#define Negro 0

/*###########################################################
	Definição da estrutura a ser usada na memória RAM
  ###########################################################
*/
typedef struct info {
	int tipo;		//1 - para imovel e 2 - para terreno.
	int objetivo;	//1 - para venda e 2 - para locação
	float preco;	//Preço do imóvel
	char endereco [100];//Endereço do Imóvel
	int disponibilidade; //1 para nao e 2 para sim.
}info;

typedef struct no {
	int codigo;		//código de indentificação
	info informacao;
	int cor;	//cor do nó.
	struct no * esq;
	struct no * dir;
}no;

/*###########################################################
	Definição da estrutura a ser usada no HD
  ###########################################################
*/

typedef struct file_no {
	int codigo;		//código de indentificação
	info informacao;
	int cor;	//cor do nó.
	int esq;
	int dir;
}file_no;


no *externo;

//Função para validar o tipo e objetivos.

int valida_tipo(void);

//Função de alocação e leitura:

no * aloca (int codigo);

//Função que aloca o nó externo
no* aloca_externo (void);

//Função que imprime a estrutura em forma de árvore

void imprime_forma(no *T,int n);



//Funcao de insercao na estrutura.

void insercao (int valor, no **filho, no **pai, no **avo, no **Arvore, int *a);

//Rotação inserção
void rotacao_insercao (no **filho, no **pai, no **avo, no **bisavo, no **Arvore, int *a);

//Funcao de remoçao na estrutura
void remove_no (int valor, no **pt, no **pai, no **avo, no **Arvore, int *a);

//Função para encontrar o nó sucessor
no* sucessor (no **pt);

//CASO 1 Da Remoção
void caso_1 (no **pai, no **irmao, no **avo, no **Arvore, int *a);

//CASO 2 Da Remoção
void caso_2 (no **pai, no **irmao, no **avo, no **Arvore, int *a);

//CASO 3 Da Remoção
void caso_3 (no **pai, no **irmao, no **avo, no **Arvore, int *a);

//CASO 4 Da Remoção
void caso_4 (no **pai, no **irmao, no **avo, no **Arvore, int *a);

//Verifica qual caso utilizar no balanceamento da árvore na remoção
void Estudo_de_caso (no **pai, no **irmao, no **avo, no **Arvore, int *a);
#endif

