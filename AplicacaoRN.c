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
Implementação das funções do arquivo AplicacaoRN.h
*/

#include "AplicacaoRN.h"
#include "ascii_estendida.h" //para caracteres

void opcao (void){
	printf ("======================================================\n\n");
	printf ("1- Inserir um novo im%cvel / terreno.\n", oagudo);
	printf ("2- Buscar um im%cvel / terreno.\n", oagudo);
	printf ("3- Excluir um im%cvel / terreno.\n", oagudo);
	printf ("4- Atualizar valor de im%cvel / terreno.\n", oagudo);
	printf ("5- Listar todos os im%cveis para venda.\n", oagudo);
	printf ("6- Listar todos os im%cveis para loca%c%co.\n", oagudo, cedilha, atil);
	printf ("7- Listar todos os terrenos para venda.\n");
	printf ("8- Listar todos os terrenos para loca%c%co.\n", cedilha, atil);
	printf ("9- Imprimir a %crvore Rubro-Negra.\n", aagudo);
	printf ("10- Sair.\n\n");
	printf ("======================================================\n\n");
	printf ("Entre com a sua op%c%co: ", cedilha, atil);
}

//Função para validar as opcoes do menu
int le_menu (void){
	int op;
	scanf ("%d", &op);
	if (op >=1 && op <=10){	//Limita as opções de acordo com o menu
		printf ("\n");
		return op;
	}
	else{
		printf ("\nOp%c%co Inv%clida.\n\nEntre com a op%c%co de acordo com o menu: ",
			cedilha, atil, aagudo,	/*caracteres da primeira linha*/
			cedilha, atil	/*caracteres da segunda linha*/
			);
		return le_menu();
	}
}

//Função que valida o código da propriedade
void le_codigo (int *elemento){
	printf ("Entre com o c%cdigo da propriedade: ", oagudo);
	scanf ("%d", elemento);
	if ((*elemento) < 1){
		printf ("\nC%cdigo inv%clido.\n\n",
			oagudo, aagudo);
		le_codigo (elemento);
	}
}

//Função que transcreve o vetor de nós em uma árvore.
//i indica a posição do vetor de acordo com a recursão na árvore.
//tam indica o tamanho atual do vetor, que cresce a medida que percorre a árvore.
void transcreve_em_vetor (no *pt, file_no *vetor, int i, int *tam){
	//visita o nó
	vetor[(*tam)].codigo = pt -> codigo;
	//Copia os dados da estrutura informação
	vetor[(*tam)].informacao = pt -> informacao;
	vetor[(*tam)].cor = pt -> cor;
	
	//visita na esquerda
	if (vetor[i].esq != 0 && vetor[i].dir != 0){	//se o indice ja estiver visitado
		i = (*tam);	//atualiza o índice para o final do vetor
	}
	if (pt -> esq == externo){	//se o nó na árvore não tiver filhos na esquerda
		vetor[i].esq = -1;
	}
	else{
		(*tam)++;	//atualiza o tamanho do vetor.
		vetor[i].esq = (*tam);	//o elemento à esquerda na árvore é o próximo elemento do vetor
		transcreve_em_vetor (pt -> esq, vetor, i+1, tam);	//manda i+1, pois quando voltar da recursão, volta com o valor de antes
	}
	//visita na direita
	if (vetor [i].esq != 0 && vetor [i].dir != 0)
		i = (*tam);
	if (pt -> dir == externo){	//se o nó na árvore não tiver filhos na direita
		vetor[i].dir = -1;
	}
	else{
		(*tam)++;
		vetor[i].dir = (*tam);
		transcreve_em_vetor (pt -> dir, vetor, i+1, tam);
	}
}

//Função que lê os dados do arquivo e passa para a memória
void leitura_arquivo (FILE **arquivo, no **arvore){
	(*arquivo) = fopen ("Dados.suv", "rb");	//Tenta abrir arquivo em modo leitura
	if ((*arquivo)){	//Se o arquivo existir
		int quant;
		int indice = 0;
		fread (&quant, sizeof (int), 1, (*arquivo));
		if (quant != -1){	//restrição para quando não houver nós no arquivo
			file_no vet_nos [quant];	//aloca o vetor com o tamanho apropriado
			fread (vet_nos, sizeof (file_no), quant, (*arquivo));
			(*arvore) = transcreve_em_arvore (indice, vet_nos);
		}
		fclose ((*arquivo));
	}
}


void gravacao_arquivo (FILE **arquivo, no **arvore, int quant){
	(*arquivo) = fopen ("Dados.suv", "wb");	//Abre no modo escrita
	if ((*arquivo)){
		if (quant == 0){	//se a árvore estiver vazia
			quant --;	//coloca quant em -1, pois senão o arquivo fica vazio, dando erro depois
			fwrite (&quant, sizeof (int), 1, (*arquivo));
		}
		else{
			file_no *vet_nos = (file_no*) calloc (quant, sizeof (file_no));	//vetor com tamanho de num. de nós na árvore
			
			int nivel = 0; int tam = 0; int num;
			transcreve_em_vetor ((*arvore), vet_nos, nivel, &tam);
			fwrite (&quant, sizeof (int), 1, (*arquivo));	//coloca no arquivo a quantidade de nós
			num = fwrite (vet_nos, sizeof (file_no), quant, (*arquivo)); //grava os nós
		}
	}
	fclose ((*arquivo));
}

//Função que vê quantos nós tem na árvore, quant tem que estar zerada na função chamadora
void calcula_num_nos (no *arvore, int *quant){
	if (arvore != externo){
		calcula_num_nos (arvore -> esq, quant);
		calcula_num_nos (arvore -> dir, quant);
		(*quant) ++;
	}
}

no * transcreve_em_arvore ( int indice, file_no * vetor ){
	if (indice == -1){
		return externo; //
	}
	else {
		no * novo = (no*) malloc ( 1 * sizeof (no) );
		novo -> codigo = vetor [indice].codigo;
		novo -> informacao = vetor [indice].informacao; /*Copia os dados do vetor para o nó*/
		novo -> cor = vetor [indice].cor;
		novo -> esq = transcreve_em_arvore (vetor[indice].esq , vetor); /*percorre o filho esquerdo*/
		novo -> dir = transcreve_em_arvore (vetor[indice].dir , vetor); /*percorre o filho direito*/
		return novo;
	}
}

//Macros para facilitar leitura de código
#define CODIGO 			pt->codigo
#define TIPO 			pt->informacao.tipo
#define OBJETIVO 		pt->informacao.objetivo
#define PRECO			pt->informacao.preco
#define ENDERECO 		pt->informacao.endereco
#define DISPONIBILIDADE	pt->informacao.disponibilidade

 void dados_do_no (no *pt){
	printf ("\n\n======================================================\n");
	printf ("C%cdigo da propriedade: %d.\n", otil, CODIGO);
	//                                          se tipo == 1   então        senão
	printf ("Tipo da propriedade: %s.\n", (TIPO == IMOVEL) ? ("Imovel") : ("Terreno"));
	printf ("Objetivo: %s.\n", (OBJETIVO == VENDA) ? ("Venda") : ("Locacao"));
	printf ("Pre%co da propriedade: R$ %.0f.\n", cedilha, PRECO);
	printf ("Endere%co: %s.\n", cedilha, ENDERECO);
	//quando for para locação:
	if (OBJETIVO == LOCACAO){
		printf ("A propriedade est%c %s para loca%c%co.\n", aagudo,
					(DISPONIBILIDADE == DISPONIVEL) ? ("disponivel") : ("indisponivel"),
					cedilha, atil);
	}
	printf ("======================================================\n\n");
 }
 
//Função que faz a busca de um imovel/terreno e imprime os dados na tela
void busca_imovel_terreno (int ident, no *pt){
	if (pt == externo)
		printf ("\nPropriedade n%co cadastrada.\n", atil);
	else
		if (pt -> codigo == ident){
			dados_do_no (pt);	//quando acha
		}
		else{
			if (ident < pt -> codigo)	//menor
				busca_imovel_terreno (ident, pt -> esq);
			else{
				if (ident > pt -> codigo) //maior
					busca_imovel_terreno (ident, pt -> dir);
			}
		}		
}

 
//Função que busca a prop. e atualiza o valor dela.

void busca_atualiza_valor (int ident, no *pt){
	if (pt == externo)
		printf ("\nPropriedade n%co cadastrada.\n", atil);
	else
		if (pt -> codigo == ident){
			printf ("\nEntre com o novo pre%co da propriedade: ", cedilha);
			scanf ("%f", &pt -> informacao.preco); //atualiza o preço
			printf ("\n");
		}
		else	//Pesquisa binária
			if (ident < pt -> codigo)
				busca_atualiza_valor (ident, pt -> esq);
			else
				busca_atualiza_valor (ident, pt -> dir);
}

//Função que imprime os dados se a prop. for imóvel e estiver à venda
void todos_imoveis_venda (no *pt){
	if (pt != externo){
		todos_imoveis_venda (pt -> esq);
		if (pt -> informacao.tipo == IMOVEL){
			if (pt -> informacao.objetivo == VENDA){
				dados_do_no (pt);	//imprime os dados
			}
		}
		todos_imoveis_venda (pt -> dir);
	}
}

//Função que imprime os dados se a prop. for imóvel e estiver para alugar
void todos_imoveis_locacao (no *pt){
	if (pt != externo){
		todos_imoveis_locacao (pt -> esq);
		if (pt -> informacao.tipo == IMOVEL){
			if (pt -> informacao.objetivo == LOCACAO){
				dados_do_no (pt);	//imprime os dados
			}
		}
		todos_imoveis_locacao (pt -> dir);
	}
}

//Função que imprime os dados se a prop. for terreno e estiver à venda
void todos_terrenos_venda (no *pt){
	if (pt != externo){
		todos_terrenos_venda (pt -> esq);
		if (pt -> informacao.tipo == TERRENO){
			if (pt -> informacao.objetivo == VENDA){
				dados_do_no (pt);	//imprime os dados
			}
		}
		todos_terrenos_venda (pt -> dir);
	}
}

//Função que imprime os dados se a prop. for terreno e estiver para alugar
void todos_terrenos_locacao (no *pt){
	if (pt != externo){
		todos_terrenos_locacao (pt -> esq);
		if (pt -> informacao.tipo == TERRENO){
			if (pt -> informacao.objetivo == LOCACAO){
				dados_do_no (pt);	//imprime os dados
			}
		}
		todos_terrenos_locacao (pt -> dir);
	}
}
