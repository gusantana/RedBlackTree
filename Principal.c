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
Arquivo principal
*/

#include "Arvore_Rubro_Negra.h"
#include "AplicacaoRN.h"

int main (){
	externo = aloca_externo (); //Nó externo com valores anulados
	no *Arvore = externo;	//Nó raiz
	//Opções, código da propriedade, impressão.
	int op, cod_prop, impressao = 0;
	//Guarda a quantidade de de nós na árvore (usado para gravar no arquivo)
	int num_nos = 0;
	//indicador de balanceamento, quantidade de itens no vetor
	int a = 0, quant_itens;
	
	FILE *Arquivo;
	
	//Inicia o programa pegando os dados do arquivo
	leitura_arquivo (&Arquivo, &Arvore);
	
	
	
	menu:
		opcao ();
		op = le_menu();
		switch (op){
			case 1:
				le_codigo (&cod_prop);	//Faz a leitura do código
				insercao (cod_prop, &Arvore, &externo, &externo, &Arvore, &a);	//Insere na árvore
				goto menu;
			case 2:
				le_codigo (&cod_prop);
				busca_imovel_terreno (cod_prop, Arvore);
				goto menu;
			case 3:
				le_codigo (&cod_prop);
				remove_no (cod_prop, &Arvore, &externo, &externo, &Arvore, &a);
				a = 0;
				goto menu;
			case 4:
				le_codigo (&cod_prop);
				busca_atualiza_valor (cod_prop, Arvore);
				goto menu;
			case 5:
				todos_imoveis_venda (Arvore);
				goto menu;
			case 6:
				todos_imoveis_locacao (Arvore);
				goto menu;
			case 7:
				todos_terrenos_venda (Arvore);
				goto menu;
			case 8:
				todos_terrenos_locacao (Arvore);
				goto menu;
			case 9:
				imprime_forma (Arvore, impressao);
				goto menu;
			case 10:
				calcula_num_nos (Arvore, &num_nos);	//vê o nº de nós
				printf ("Saindo...\n");
				gravacao_arquivo (&Arquivo, &Arvore, num_nos);	//grava no arquivo
				break;
		}
		
    return 0;
}
