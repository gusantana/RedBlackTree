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
2� Arquivo Header
*/

#ifndef __AplicacaoRN__
#define __AplicacaoRN__

#include "Arvore_Rubro_Negra.h"

//Fun��o das op��es do menu
void opcao (void);

//Fun��o que valida as op��es do menu
int le_menu (void);

//Fun��o que valida o c�digo da propriedade
void le_codigo (int *elemento);

//Fun��o que l� os dados do arquivo e passa para a mem�ria
void leitura_arquivo (FILE **arquivo, no **arvore);

//Fun��o que transcreve o vetor de n�s em uma �rvore
void transcreve_em_vetor (no *pt, file_no *vetor, int i, int *tam);

//Fun��o que grava o arquivo
void gravacao_arquivo (FILE **arquivo, no **arvore, int quant);

//Fun��o que v� quantos n�s tem na �rvore
void calcula_num_nos (no *arvore, int *quant);

//Fun��o que transforma o vetor em �rvore
no* transcreve_em_arvore (int indice, file_no * vetor);

//Fun��o que faz a busca de um imovel/terreno e imprime os dados na tela
void busca_imovel_terreno (int ident, no *pt);

//Func�o que mostra os dados do n�
void dados_do_no (no *pt);

//Fun��o que busca a prop. e atualiza o valor dela.
void busca_atualiza_valor (int ident, no *pt);

//Fun��o que imprime os dados se a prop. for im�vel e estiver � venda
void todos_imoveis_venda (no *pt);

//Fun��o que imprime os dados se a prop. for im�vel e estiver para alugar
void todos_imoveis_locacao (no *pt);

//Fun��o que imprime os dados se a prop. for terreno e estiver � venda
void todos_terrenos_venda (no *pt);

//Fun��o que imprime os dados se a prop. for terreno e estiver para alugar
void todos_terrenos_locacao (no *pt);


#endif
