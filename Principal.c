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
Arquivo principal
*/

#include "Arvore_Rubro_Negra.h"
#include "AplicacaoRN.h"

int main (){
	externo = aloca_externo (); //N� externo com valores anulados
	no *Arvore = externo;	//N� raiz
	//Op��es, c�digo da propriedade, impress�o.
	int op, cod_prop, impressao = 0;
	//Guarda a quantidade de de n�s na �rvore (usado para gravar no arquivo)
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
				le_codigo (&cod_prop);	//Faz a leitura do c�digo
				insercao (cod_prop, &Arvore, &externo, &externo, &Arvore, &a);	//Insere na �rvore
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
				calcula_num_nos (Arvore, &num_nos);	//v� o n� de n�s
				printf ("Saindo...\n");
				gravacao_arquivo (&Arquivo, &Arvore, num_nos);	//grava no arquivo
				break;
		}
		
    return 0;
}
