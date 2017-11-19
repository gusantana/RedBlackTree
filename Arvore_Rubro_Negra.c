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
Implementa�ao das fun��es do arquivo Arvore_Rubro_Negra.h
*/
#include "Arvore_Rubro_Negra.h"
#include "ascii_estendida.h" //para caracteres


//Fun��o para validar o tipo e objetivos.

int valida_tipo(void){		// 1 Para Im�vel - 2 Para Terreno
	int op;		
	scanf ("%d", &op);		//L� a op��o desejada
	if (op != 1 && op != 2){	//caso a op��o nao seja 1 ou 2.
		printf ("\nEntrada inv%clida, digite novamente.\n", aagudo);
		op = valida_tipo ();
	}
	return op;		//Retorna o tipo v�lido lido.
}

void imprime_forma(no *T,int n){//inicialmente o 'n' tem valor 0 
  
  if (T != externo)
  {
	imprime_forma(T -> dir,n+1);//a cada chama recursiva do programa o n recebe +1;
    for(int i = 0; i < n; i++){
		printf("\t");//O la�o for vai de i a n imprimindo \t ... isso causa o efeito de ARVORE =)
	}
    printf ("%d cor: %s\n", T -> codigo, (T -> cor == RUBRO) ? ("Rubro") : ("Negro"));
    imprime_forma (T -> esq, n+1);//a cada chama recursiva do programa o n recebe +1;
  }
}

// Fun��o para aloca��o de um n� externo
no* aloca_externo (void){
	no *aux = (no*) malloc (sizeof (no));
	//Anula os valores do n� externo
	aux -> codigo = 0;
	aux -> informacao.tipo = -1;
	aux -> informacao.objetivo = -1;
	aux -> informacao.preco = -1;
	aux -> informacao.disponibilidade = -1;
	
	aux -> cor = NEGRO;
	aux -> esq = NULL;
	aux -> dir = NULL;
	
	return aux;
}

//Fun��o de aloca��o e leitura:

no* aloca (int codigo){
	no *novo = (no*) malloc (sizeof (no));
	char enter;
	novo -> codigo = codigo;
	// Recebe informa��o se a propriedade � um im�vel ou um terreno
	printf ("\nEntre com o tipo de propriedade: \n1 - Para Im%cvel;\n2 - Para Terreno.\n", otil);
	novo -> informacao.tipo = valida_tipo();
	
	fflush (stdin);
	// Se a propriedade � para venda ou loca��o
	printf ("\nObjetivo: \n1 - Venda;\n2 - Loca%c%co.\n", cedilha, atil);
	novo -> informacao.objetivo = valida_tipo ();
	// Recebe o pre�o da propriedade
	printf ("\nDigite o pre%co da propriedade: R$ ", cedilha);
	scanf ("%f", &novo -> informacao.preco);
	
	fflush (stdin);
	// Recebe o Endere�o da propriedade
	printf ("\nDigite o endere%co da propriedade: ", cedilha);
	// scanf ("[^\n]", novo -> informacao.endereco);
	gets (novo -> informacao.endereco);
	
	fflush (stdin);
	
	if (novo -> informacao.objetivo == LOCACAO){ // Se o obejetivo for para loca��o, informa se esta dispon�vel ou n�o
		printf ("\nDigite a op%c%co de disponibilidade da propriedade:\n1 - Indispon%cvel\n2 - Dispon%cvel: ",
			cedilha, atil, iagudo, iagudo);
		novo -> informacao.disponibilidade = valida_tipo();
	}
	else
		novo -> informacao.disponibilidade = -1;	//Disponibilidade anulada
	
	fflush (stdin);
	
	printf ("\n\n");
	
	novo -> cor = RUBRO;
	novo -> esq = externo;
	novo -> dir = externo;
	
	return (novo);
}


//Funcao de insercao da estrutura.

void insercao (int valor, no **filho, no **pai, no **avo, no **Arvore, int *a){
	no * afilhado;
	//aloca o n� na �rvore
	if ( (*filho) == externo ){
		(*filho) = aloca (valor);
		if ((*filho) == (*Arvore)){	//Quando � inserido o n� raiz
			(*filho) -> cor = NEGRO;
		}
		else{
			if (valor < (*pai) -> codigo){	//pai aponta para o filho na esquerda
				(*pai) -> esq = (*filho);
			}
			else{	//pai aponta para o filho na direita
				(*pai) -> dir = (*filho);
			}
		}
		(*a) = 1;	//como houve altera��o na �rvore, a � setado em 1.
	}
	else{	//percorre a �rvore
		if (valor != (*filho) -> codigo){	//verifica se n�o tem outro valor igual
			if (valor < (*filho) -> codigo)
				afilhado = (*filho) -> esq; //se � menor procura na esquerda
			else
				afilhado = (*filho) -> dir; // se � maior procura na direita
			insercao (valor, &afilhado, filho, pai, Arvore, a); //Faz a procura novamente
			if ((*a) == 1) 
				rotacao_insercao (&afilhado, filho, pai, avo, Arvore, a); //Se houve inser��o, verifica se precisa balancear
			else{
				if ((*a) == 0) //Sobe duas recurs�es para ver se precisa balancear
					(*a) = 1;
			}
		}
		else{	//quando j� tem elemento na �rvore
			printf ("Inser%c%co Inv%clida.\n", cedilha, atil, aagudo);
		}
	}
	(*Arvore) -> cor = NEGRO;
}

void rotacao_insercao (no **filho, no **pai, no **avo, no **bisavo, no **Arvore, int *a){
	no *aux, *tio;	//aux indica a raiz da sub�rvore a ser rotacionada
		//tio � o tio do filho
	
	(*a) = 2;	//sinaliza a flag que n�o precisa balancear mais
	if ((*avo) != externo){	//Se av� existe
		aux = (*avo);
		if ((*pai) -> cor == RUBRO){
			if ((*pai) == (*avo) -> esq)	//Define onde tio est�
				tio = (*avo) -> dir;
			else
				tio = (*avo) -> esq;
			//Depois de ter definido o tio, verificar os casos
			if (tio -> cor == RUBRO){	//Caso 2.1
				(*pai) -> cor = NEGRO;	//Se o tio for rubro, s� troca as cores
				(*avo) -> cor = RUBRO;
				tio -> cor = NEGRO;	//definindo a raiz da sub-�rvore Rubro e seus filhos Negro
				(*a) = 0;
			}
			else{
				(*avo) -> cor = RUBRO; //Coloca o av� Rubro
				if ((*filho) == (*pai) ->esq){
					if ((*pai) == (*avo) -> esq){	//Caso 2.2.1	ROTA��O SIMPLES DIREITA
						aux = (*pai);	//define o pai como raiz
						(*avo) -> esq = (*pai) -> dir;
						(*pai) -> dir = (*avo);
						//Atualiza a cor
						(*pai) -> cor = NEGRO;
					}
					else{ //Caso 2.2.2	//ROTA��O DUPLA ESQUERDA
						aux = (*filho);	//define filho como raiz da sub-�rvore
						(*avo) -> dir = (*filho) -> esq;
						(*pai) -> esq = (*filho) -> dir;
						(*filho) -> esq = (*avo);
						(*filho) -> dir = (*pai);
						//Atualiza a cor
						(*filho) -> cor = Negro;
					}
				}
				else{
					if ((*pai) == (*avo) -> dir){	//Caso 2.2.3 ROTA��O SIMPLES ESQUERDA
						aux = (*pai); //define o pai como raiz
						(*avo) -> dir = (*pai) -> esq;
						(*pai) -> esq = (*avo);
						//Atualiza a cor
						(*pai) -> cor = NEGRO;
					}
					else{
						aux = (*filho);	//define o filho como raiz da sub-�rvore
						(*avo) -> esq = (*filho) -> dir;
						(*pai) -> dir = (*filho) -> esq;
						(*filho) -> dir = (*avo);
						(*filho) -> esq = (*pai);
						//Atualiza a cor
						(*filho) -> cor = NEGRO;
					}
				}
			}
		}
		if ((*bisavo) != externo){	//se a sub-�rvore faz parte de uma �rvore acima
			if ((*filho) -> codigo < (*bisavo) -> codigo)
				(*bisavo) -> esq = aux;
			else
				(*bisavo) -> dir = aux;
		}
		else{
			(*Arvore) = aux;
			(*Arvore) -> cor = NEGRO; //A raiz da �rvore � sempre Negra
		}
	}
}


void Estudo_de_caso (no **pai, no **irmao, no **avo, no **Arvore,int *a){
	//Verifica o Caso 1 e o Caso 2, porque eles n�o dependem da posi��o do filho com o pai
	if ((*irmao)-> cor == NEGRO && (*irmao)->dir->cor == NEGRO && (*irmao)->esq->cor == NEGRO){
		caso_2 (pai, irmao, avo, Arvore, a);
		//Verificar Caso 2: O irmao � Negro com dois filhos Negros.
	}
	else{
		if ((*irmao)->cor == RUBRO && (*irmao)->esq->cor == NEGRO && (*irmao)->dir->cor == NEGRO){
			caso_1 (pai, irmao, avo, Arvore, a);
			//Verificar Caso 1: O irm�o � Rubro com dois filhos Negros.
		}
		//Os seguintes casos dependem da posi��o do filho com o pai
		else{
			if ((*irmao) == (*pai) -> dir){	//Irm�o � filho � direita
				if ( (*irmao)->cor == NEGRO && (*irmao)->esq->cor == RUBRO && (*irmao)->dir->cor == NEGRO){
					caso_3 ( pai, irmao, avo, Arvore, a);
					//Verificar Caso 3: Irmao � Negro, filho da esquerda � RUBRO, filho da direita � NEGRO.
				}
				else{
					if ( (*irmao)->cor == NEGRO && (*irmao)->dir->cor == RUBRO){
						caso_4 ( pai, irmao, avo, Arvore, a);
						//Verificar Caso 4: Irmao � Negro, seu filho direito � RUBRO.
					}
				}
			}
			else{ //Irm�o � filho � esquerda
				if ((*irmao) -> cor == NEGRO && (*irmao) -> dir -> cor == RUBRO && (*irmao) -> esq -> cor == NEGRO){
					caso_3 (pai, irmao, avo, Arvore, a);
					//Verificar Caso 3: Irmao � Negro, filho da direita � RUBRO, filho da esquerda � NEGRO.
				}
				else{
					if ( (*irmao) -> cor == NEGRO && (*irmao) -> esq -> cor == RUBRO){
						caso_4 (pai, irmao, avo, Arvore, a);
						//Verificar Caso 4: Irmao � Negro, seu filho esquerdo � RUBRO.
					}
				}
			}
		}
	}
}


//Caso 1 da Remo��o
void caso_1 (no **pai, no**irmao, no **avo, no **Arvore, int *a){   //Inverte as cores do pai e do irm�o
	no *filho_do_pai, *novo_pai;
	if ((*pai) -> dir == (*irmao)){    //Caso da direita
		(*pai) -> dir = (*irmao) -> esq;
		(*irmao) -> esq = (*pai);    //Faz a rota��o � esquerda
		(*pai) -> cor = RUBRO;   
		(*irmao) -> cor = NEGRO;	//Pai fica rubro e irmao fica negro e � o novo n� raiz da sub-�rvore.
		filho_do_pai = (*pai)->dir;	//O novo irm�o � filho � direita do pai
		novo_pai = (*pai);	//Novo pai para verificar outros casos
	}
	else{    //Caso da esquerda
		(*pai) -> esq = (*irmao) -> dir;    //Faz a rota��o � direita
		(*irmao) -> dir = (*pai);
		(*pai) -> cor = RUBRO;   //Atualiza as cores
		(*irmao) -> cor = NEGRO;	//Pai fica rubro e irmao fica negro e � o novo n� raiz da sub-�rvore.
		filho_do_pai = (*pai) -> esq;	//O novo irm�o � filho � esquerda do pai
		novo_pai = (*pai);	//Novo pai para verificar outros casos
	}
	if ((*Arvore) == (*pai)){	//se n�o for sub-�rvore
		pai = irmao;
		(*Arvore) = (*pai);
	}
	else{
		if ((*avo) -> dir == (*pai)){	//atualiza o av�
			pai = irmao;
			(*avo) -> dir = (*pai);
		}
		else{
			pai = irmao;
			(*avo) -> esq = (*pai);
		}
	}
	//analisa os casos novamente
	Estudo_de_caso (&novo_pai, &filho_do_pai, pai, Arvore, a);
}



//Caso 2 da Remo��o
void caso_2 (no **pai, no **irmao, no **avo, no **Arvore, int *a){
	(*irmao) -> cor = RUBRO;	//seta o irm�o Rubro, e o pai Negro.
	if ((*pai) -> cor == RUBRO){
		(*a) = 0;
		(*pai) -> cor = NEGRO;
	}
	else{
		if ((*pai) == (*Arvore))	//se o pai � o n� raiz, n�o precisa subir na recurs�o
			(*a) = 0;
		else{
			(*a) = 1;	//Se o pai for Negro, sobe na recurs�o
		}
	}
}


//Caso 3 da Remo��o
void caso_3 (no **pai, no **irmao, no **avo, no **Arvore, int *a){
	no *filho_do_irmao;
	if ((*pai) -> dir == (*irmao)){
		filho_do_irmao = (*irmao) -> esq;
		//ROTAC�O PARA DIREITA

		(*irmao) -> esq = filho_do_irmao -> dir;
		filho_do_irmao -> dir = (*irmao);
		(*pai) -> dir = filho_do_irmao;
		//ATUALIZAR AS CORES

		(*irmao) -> cor = RUBRO;
		filho_do_irmao -> cor = NEGRO;
		
		//atualiza o ponteiro do irm�o
		irmao = &filho_do_irmao;
		//Analiza outros poss�veis casos
		Estudo_de_caso (pai, irmao, avo, Arvore, a);
	}
	else{
		filho_do_irmao = (*irmao) -> dir;
		//ROTA��O PARA ESQUERDA

		(*irmao) -> dir = filho_do_irmao -> esq;
		filho_do_irmao -> esq = (*irmao);
		(*pai) -> esq = filho_do_irmao;
		//ATUALIZAR AS CORES

		(*irmao) -> cor = RUBRO;
		filho_do_irmao -> cor = NEGRO;
		
		//atualiza o ponteiro do irm�o
		irmao = &filho_do_irmao;
		//Analiza outros poss�veis casos
		Estudo_de_caso (pai, irmao, avo, Arvore, a);
	}
}


//Caso 4 da Remo��o
void caso_4 (no **pai, no **irmao, no **avo, no **Arvore, int *a){
	//Primeiro faz a troca de cores do pai e do irmao
	//e depois verifica os casos da diereita e esquerda
	(*irmao) -> cor = (*pai) -> cor;
	(*pai) -> cor = NEGRO;
	if ((*pai) -> dir == (*irmao)){	//Quando o irmao � filho � direita do pai
		(*irmao) -> dir -> cor = NEGRO;
		//ROTA��O PARA ESQUERDA
		(*pai) -> dir = (*irmao) -> esq;
		(*irmao) -> esq = (*pai);
	}
	else{
		(*irmao) -> esq -> cor = NEGRO;
		//ROTA��O PARA DIREITA
		(*pai) -> esq = (*irmao) -> dir;
		(*irmao) -> dir  = (*pai);
	}
	//Atualiza o n� raiz
	if ((*Arvore) == (*pai)){	
		pai = irmao;
		(*Arvore) = (*pai);
	}
	else{
		if ((*avo) -> esq == (*pai)){	//Atualiza o ponteiro do av�
			pai = irmao;
			(*avo) -> esq = (*pai);
		}
		else{
			pai = irmao;
			(*avo) -> dir = (*pai);
		}
	}
	(*a) = 0;
}


//Achar o sucessor
no* sucessor (no **pt){
	//(*pai) = (*pt);
	no *aux = (*pt) -> dir;
	while (aux -> esq != externo){ //percorre at� o elemento mais � esquerda da �rvore
		//(*pai) = aux;
		aux = aux -> esq;
	}
	return aux;
}

//Fun��o de Remo��o do n�
void remove_no (int valor, no **pt, no **pai, no **avo, no **Arvore, int *a){
	// Verifica logo se a �rvore est� vazia ou se o elemento existe nela
	if ((*pt) == externo){
		printf ("Propriedade n%co existente.\n", atil);
	}
	else{
		if ((*pt) -> codigo == valor){ //Acha e remove o n�
			if ((*pt) -> dir != externo){
				no *suc = sucessor (pt); //procura o sucessor.
				
				//Troca as informa��es
				(*pt) -> codigo = suc -> codigo;
				(*pt) ->  informacao = suc -> informacao;
				//Depois que troca as informa��es com o sucessor,
				//procura o sucessor para remov�-lo.
				
				remove_no (suc -> codigo, &((*pt) -> dir), pt, pai, Arvore, a);
			}
			else{ //Quando n�o tem sucessor � direita
				no *temp;
				
				printf ("Cadastro exclu%cdo com sucesso.\n", iagudo);
				if ((*pt) -> cor == RUBRO){ //Se o n� for Rubro, simplesmente desaloca ele.
					free ((*pt));
					(*pt) = externo;
				}
				else{ //Quando o n� � Negro
					//V� se o n� pt � filho � direita ou � esquerda.
					no *irmao;
					//Se for o n� raiz, nao precisa verificar o pai.
					if ((*pt) != (*Arvore)){
					   /*Se o n� PT for filho       Irmao se torna filho    Sen�o Irmao se torna filho
					   � esquerda do pai             � direita do pai        � esquerda do pai */
						((*pai) -> dir == (*pt)) ? (irmao = (*pai) -> esq) : (irmao = (*pai) -> dir);
					}
					temp = (*pt) -> esq;	//referencia o filho � esquerda, remove o n�.
					free ((*pt));
					(*pt) = temp;
					(*pt) -> cor = NEGRO;	//O filho pega a cor do n� anterior
					
					if ((*pt) == externo){
						Estudo_de_caso (pai, &irmao, avo, Arvore, a);
					}
					
				}
			}
		}
		else{
			no *irmao;
			
			if (valor < (*pt) -> codigo){ //Procura na esquerda
				remove_no (valor, &((*pt) -> esq), pt, pai, Arvore, a);
				if ((*a) == 1){
					/*Se o n� PT for filho       Irmao se torna filho    Sen�o Irmao se torna filho
					� direita do pai             � esquerda do pai        � direita do pai */
					((*pai) -> dir == (*pt)) ? (irmao = (*pai) -> esq) : (irmao = (*pai) -> dir);
					Estudo_de_caso (pai, &irmao, avo, Arvore, a);
				}
			}
			else{
				remove_no (valor, &((*pt) -> dir), pt, pai, Arvore, a);
				if ((*a) == 1){
					/*Se o n� PT for filho       Irmao se torna filho    Sen�o Irmao se torna filho
					� direita do pai             � esquerda do pai        � direita do pai */
					((*pai) -> dir == (*pt)) ? (irmao = (*pai) -> esq) : (irmao = (*pai) -> dir);
					Estudo_de_caso (pai, &irmao, avo, Arvore, a);
				}
			}
		}
	}
	(*Arvore) -> cor = NEGRO;
}

