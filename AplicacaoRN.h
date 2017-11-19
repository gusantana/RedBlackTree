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
2º Arquivo Header
*/

#ifndef __AplicacaoRN__
#define __AplicacaoRN__

#include "Arvore_Rubro_Negra.h"

//Função das opções do menu
void opcao (void);

//Função que valida as opções do menu
int le_menu (void);

//Função que valida o código da propriedade
void le_codigo (int *elemento);

//Função que lê os dados do arquivo e passa para a memória
void leitura_arquivo (FILE **arquivo, no **arvore);

//Função que transcreve o vetor de nós em uma árvore
void transcreve_em_vetor (no *pt, file_no *vetor, int i, int *tam);

//Função que grava o arquivo
void gravacao_arquivo (FILE **arquivo, no **arvore, int quant);

//Função que vê quantos nós tem na árvore
void calcula_num_nos (no *arvore, int *quant);

//Função que transforma o vetor em árvore
no* transcreve_em_arvore (int indice, file_no * vetor);

//Função que faz a busca de um imovel/terreno e imprime os dados na tela
void busca_imovel_terreno (int ident, no *pt);

//Funcão que mostra os dados do nó
void dados_do_no (no *pt);

//Função que busca a prop. e atualiza o valor dela.
void busca_atualiza_valor (int ident, no *pt);

//Função que imprime os dados se a prop. for imóvel e estiver à venda
void todos_imoveis_venda (no *pt);

//Função que imprime os dados se a prop. for imóvel e estiver para alugar
void todos_imoveis_locacao (no *pt);

//Função que imprime os dados se a prop. for terreno e estiver à venda
void todos_terrenos_venda (no *pt);

//Função que imprime os dados se a prop. for terreno e estiver para alugar
void todos_terrenos_locacao (no *pt);


#endif
