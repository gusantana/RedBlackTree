/*Trabalho Estrutura de Dados 2
Universidade Federal do Mato Grosso
Instituto de Ci�ncias Exatas e da Terra
Ci�ncia da Computa��o

Docente: Luciana Lee

Grupo 4:
	Gustavo Santana Coelho;
	Guilherme Santana Coelho;
	Vitor Rezende Campos.

Exerc�cio 2.
1� Arquivo Header
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

//Disponibilidade (Loca��o apenas)
#define INDISPONIVEL 1
#define DISPONIVEL 2

//Cor do n�:
#define RUBRO 1
#define Rubro 1

#define NEGRO 0
#define Negro 0

/*###########################################################
	Defini��o da estrutura a ser usada na mem�ria RAM
  ###########################################################
*/
typedef struct info {
	int tipo;		//1 - para imovel e 2 - para terreno.
	int objetivo;	//1 - para venda e 2 - para loca��o
	float preco;	//Pre�o do im�vel
	char endereco [100];//Endere�o do Im�vel
	int disponibilidade; //1 para nao e 2 para sim.
}info;

typedef struct no {
	int codigo;		//c�digo de indentifica��o
	info informacao;
	int cor;	//cor do n�.
	struct no * esq;
	struct no * dir;
}no;

/*###########################################################
	Defini��o da estrutura a ser usada no HD
  ###########################################################
*/

typedef struct file_no {
	int codigo;		//c�digo de indentifica��o
	info informacao;
	int cor;	//cor do n�.
	int esq;
	int dir;
}file_no;


no *externo;

//Fun��o para validar o tipo e objetivos.

int valida_tipo(void);

//Fun��o de aloca��o e leitura:

no * aloca (int codigo);

//Fun��o que aloca o n� externo
no* aloca_externo (void);

//Fun��o que imprime a estrutura em forma de �rvore

void imprime_forma(no *T,int n);



//Funcao de insercao na estrutura.

void insercao (int valor, no **filho, no **pai, no **avo, no **Arvore, int *a);

//Rota��o inser��o
void rotacao_insercao (no **filho, no **pai, no **avo, no **bisavo, no **Arvore, int *a);

//Funcao de remo�ao na estrutura
void remove_no (int valor, no **pt, no **pai, no **avo, no **Arvore, int *a);

//Fun��o para encontrar o n� sucessor
no* sucessor (no **pt);

//CASO 1 Da Remo��o
void caso_1 (no **pai, no **irmao, no **avo, no **Arvore, int *a);

//CASO 2 Da Remo��o
void caso_2 (no **pai, no **irmao, no **avo, no **Arvore, int *a);

//CASO 3 Da Remo��o
void caso_3 (no **pai, no **irmao, no **avo, no **Arvore, int *a);

//CASO 4 Da Remo��o
void caso_4 (no **pai, no **irmao, no **avo, no **Arvore, int *a);

//Verifica qual caso utilizar no balanceamento da �rvore na remo��o
void Estudo_de_caso (no **pai, no **irmao, no **avo, no **Arvore, int *a);
#endif

