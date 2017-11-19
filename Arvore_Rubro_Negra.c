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
Implementaçao das funções do arquivo Arvore_Rubro_Negra.h
*/
#include "Arvore_Rubro_Negra.h"
#include "ascii_estendida.h" //para caracteres


//Função para validar o tipo e objetivos.

int valida_tipo(void){		// 1 Para Imóvel - 2 Para Terreno
	int op;		
	scanf ("%d", &op);		//Lê a opção desejada
	if (op != 1 && op != 2){	//caso a opção nao seja 1 ou 2.
		printf ("\nEntrada inv%clida, digite novamente.\n", aagudo);
		op = valida_tipo ();
	}
	return op;		//Retorna o tipo válido lido.
}

void imprime_forma(no *T,int n){//inicialmente o 'n' tem valor 0 
  
  if (T != externo)
  {
	imprime_forma(T -> dir,n+1);//a cada chama recursiva do programa o n recebe +1;
    for(int i = 0; i < n; i++){
		printf("\t");//O laço for vai de i a n imprimindo \t ... isso causa o efeito de ARVORE =)
	}
    printf ("%d cor: %s\n", T -> codigo, (T -> cor == RUBRO) ? ("Rubro") : ("Negro"));
    imprime_forma (T -> esq, n+1);//a cada chama recursiva do programa o n recebe +1;
  }
}

// Função para alocação de um nó externo
no* aloca_externo (void){
	no *aux = (no*) malloc (sizeof (no));
	//Anula os valores do nó externo
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

//Função de alocação e leitura:

no* aloca (int codigo){
	no *novo = (no*) malloc (sizeof (no));
	char enter;
	novo -> codigo = codigo;
	// Recebe informação se a propriedade é um imóvel ou um terreno
	printf ("\nEntre com o tipo de propriedade: \n1 - Para Im%cvel;\n2 - Para Terreno.\n", otil);
	novo -> informacao.tipo = valida_tipo();
	
	fflush (stdin);
	// Se a propriedade é para venda ou locação
	printf ("\nObjetivo: \n1 - Venda;\n2 - Loca%c%co.\n", cedilha, atil);
	novo -> informacao.objetivo = valida_tipo ();
	// Recebe o preço da propriedade
	printf ("\nDigite o pre%co da propriedade: R$ ", cedilha);
	scanf ("%f", &novo -> informacao.preco);
	
	fflush (stdin);
	// Recebe o Endereço da propriedade
	printf ("\nDigite o endere%co da propriedade: ", cedilha);
	// scanf ("[^\n]", novo -> informacao.endereco);
	gets (novo -> informacao.endereco);
	
	fflush (stdin);
	
	if (novo -> informacao.objetivo == LOCACAO){ // Se o obejetivo for para locação, informa se esta disponível ou não
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
	//aloca o nó na Árvore
	if ( (*filho) == externo ){
		(*filho) = aloca (valor);
		if ((*filho) == (*Arvore)){	//Quando é inserido o nó raiz
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
		(*a) = 1;	//como houve alteração na árvore, a é setado em 1.
	}
	else{	//percorre a Árvore
		if (valor != (*filho) -> codigo){	//verifica se não tem outro valor igual
			if (valor < (*filho) -> codigo)
				afilhado = (*filho) -> esq; //se é menor procura na esquerda
			else
				afilhado = (*filho) -> dir; // se é maior procura na direita
			insercao (valor, &afilhado, filho, pai, Arvore, a); //Faz a procura novamente
			if ((*a) == 1) 
				rotacao_insercao (&afilhado, filho, pai, avo, Arvore, a); //Se houve inserção, verifica se precisa balancear
			else{
				if ((*a) == 0) //Sobe duas recursões para ver se precisa balancear
					(*a) = 1;
			}
		}
		else{	//quando já tem elemento na árvore
			printf ("Inser%c%co Inv%clida.\n", cedilha, atil, aagudo);
		}
	}
	(*Arvore) -> cor = NEGRO;
}

void rotacao_insercao (no **filho, no **pai, no **avo, no **bisavo, no **Arvore, int *a){
	no *aux, *tio;	//aux indica a raiz da subárvore a ser rotacionada
		//tio é o tio do filho
	
	(*a) = 2;	//sinaliza a flag que não precisa balancear mais
	if ((*avo) != externo){	//Se avô existe
		aux = (*avo);
		if ((*pai) -> cor == RUBRO){
			if ((*pai) == (*avo) -> esq)	//Define onde tio está
				tio = (*avo) -> dir;
			else
				tio = (*avo) -> esq;
			//Depois de ter definido o tio, verificar os casos
			if (tio -> cor == RUBRO){	//Caso 2.1
				(*pai) -> cor = NEGRO;	//Se o tio for rubro, só troca as cores
				(*avo) -> cor = RUBRO;
				tio -> cor = NEGRO;	//definindo a raiz da sub-árvore Rubro e seus filhos Negro
				(*a) = 0;
			}
			else{
				(*avo) -> cor = RUBRO; //Coloca o avô Rubro
				if ((*filho) == (*pai) ->esq){
					if ((*pai) == (*avo) -> esq){	//Caso 2.2.1	ROTAÇÃO SIMPLES DIREITA
						aux = (*pai);	//define o pai como raiz
						(*avo) -> esq = (*pai) -> dir;
						(*pai) -> dir = (*avo);
						//Atualiza a cor
						(*pai) -> cor = NEGRO;
					}
					else{ //Caso 2.2.2	//ROTAÇÃO DUPLA ESQUERDA
						aux = (*filho);	//define filho como raiz da sub-árvore
						(*avo) -> dir = (*filho) -> esq;
						(*pai) -> esq = (*filho) -> dir;
						(*filho) -> esq = (*avo);
						(*filho) -> dir = (*pai);
						//Atualiza a cor
						(*filho) -> cor = Negro;
					}
				}
				else{
					if ((*pai) == (*avo) -> dir){	//Caso 2.2.3 ROTAÇÃO SIMPLES ESQUERDA
						aux = (*pai); //define o pai como raiz
						(*avo) -> dir = (*pai) -> esq;
						(*pai) -> esq = (*avo);
						//Atualiza a cor
						(*pai) -> cor = NEGRO;
					}
					else{
						aux = (*filho);	//define o filho como raiz da sub-árvore
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
		if ((*bisavo) != externo){	//se a sub-árvore faz parte de uma árvore acima
			if ((*filho) -> codigo < (*bisavo) -> codigo)
				(*bisavo) -> esq = aux;
			else
				(*bisavo) -> dir = aux;
		}
		else{
			(*Arvore) = aux;
			(*Arvore) -> cor = NEGRO; //A raiz da árvore é sempre Negra
		}
	}
}


void Estudo_de_caso (no **pai, no **irmao, no **avo, no **Arvore,int *a){
	//Verifica o Caso 1 e o Caso 2, porque eles não dependem da posição do filho com o pai
	if ((*irmao)-> cor == NEGRO && (*irmao)->dir->cor == NEGRO && (*irmao)->esq->cor == NEGRO){
		caso_2 (pai, irmao, avo, Arvore, a);
		//Verificar Caso 2: O irmao é Negro com dois filhos Negros.
	}
	else{
		if ((*irmao)->cor == RUBRO && (*irmao)->esq->cor == NEGRO && (*irmao)->dir->cor == NEGRO){
			caso_1 (pai, irmao, avo, Arvore, a);
			//Verificar Caso 1: O irmão é Rubro com dois filhos Negros.
		}
		//Os seguintes casos dependem da posição do filho com o pai
		else{
			if ((*irmao) == (*pai) -> dir){	//Irmão é filho à direita
				if ( (*irmao)->cor == NEGRO && (*irmao)->esq->cor == RUBRO && (*irmao)->dir->cor == NEGRO){
					caso_3 ( pai, irmao, avo, Arvore, a);
					//Verificar Caso 3: Irmao é Negro, filho da esquerda é RUBRO, filho da direita é NEGRO.
				}
				else{
					if ( (*irmao)->cor == NEGRO && (*irmao)->dir->cor == RUBRO){
						caso_4 ( pai, irmao, avo, Arvore, a);
						//Verificar Caso 4: Irmao é Negro, seu filho direito é RUBRO.
					}
				}
			}
			else{ //Irmão é filho à esquerda
				if ((*irmao) -> cor == NEGRO && (*irmao) -> dir -> cor == RUBRO && (*irmao) -> esq -> cor == NEGRO){
					caso_3 (pai, irmao, avo, Arvore, a);
					//Verificar Caso 3: Irmao é Negro, filho da direita é RUBRO, filho da esquerda é NEGRO.
				}
				else{
					if ( (*irmao) -> cor == NEGRO && (*irmao) -> esq -> cor == RUBRO){
						caso_4 (pai, irmao, avo, Arvore, a);
						//Verificar Caso 4: Irmao é Negro, seu filho esquerdo é RUBRO.
					}
				}
			}
		}
	}
}


//Caso 1 da Remoção
void caso_1 (no **pai, no**irmao, no **avo, no **Arvore, int *a){   //Inverte as cores do pai e do irmão
	no *filho_do_pai, *novo_pai;
	if ((*pai) -> dir == (*irmao)){    //Caso da direita
		(*pai) -> dir = (*irmao) -> esq;
		(*irmao) -> esq = (*pai);    //Faz a rotação à esquerda
		(*pai) -> cor = RUBRO;   
		(*irmao) -> cor = NEGRO;	//Pai fica rubro e irmao fica negro e é o novo nó raiz da sub-árvore.
		filho_do_pai = (*pai)->dir;	//O novo irmão é filho à direita do pai
		novo_pai = (*pai);	//Novo pai para verificar outros casos
	}
	else{    //Caso da esquerda
		(*pai) -> esq = (*irmao) -> dir;    //Faz a rotação à direita
		(*irmao) -> dir = (*pai);
		(*pai) -> cor = RUBRO;   //Atualiza as cores
		(*irmao) -> cor = NEGRO;	//Pai fica rubro e irmao fica negro e é o novo nó raiz da sub-árvore.
		filho_do_pai = (*pai) -> esq;	//O novo irmão é filho à esquerda do pai
		novo_pai = (*pai);	//Novo pai para verificar outros casos
	}
	if ((*Arvore) == (*pai)){	//se não for sub-árvore
		pai = irmao;
		(*Arvore) = (*pai);
	}
	else{
		if ((*avo) -> dir == (*pai)){	//atualiza o avô
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



//Caso 2 da Remoção
void caso_2 (no **pai, no **irmao, no **avo, no **Arvore, int *a){
	(*irmao) -> cor = RUBRO;	//seta o irmão Rubro, e o pai Negro.
	if ((*pai) -> cor == RUBRO){
		(*a) = 0;
		(*pai) -> cor = NEGRO;
	}
	else{
		if ((*pai) == (*Arvore))	//se o pai é o nó raiz, não precisa subir na recursão
			(*a) = 0;
		else{
			(*a) = 1;	//Se o pai for Negro, sobe na recursão
		}
	}
}


//Caso 3 da Remoção
void caso_3 (no **pai, no **irmao, no **avo, no **Arvore, int *a){
	no *filho_do_irmao;
	if ((*pai) -> dir == (*irmao)){
		filho_do_irmao = (*irmao) -> esq;
		//ROTACÃO PARA DIREITA

		(*irmao) -> esq = filho_do_irmao -> dir;
		filho_do_irmao -> dir = (*irmao);
		(*pai) -> dir = filho_do_irmao;
		//ATUALIZAR AS CORES

		(*irmao) -> cor = RUBRO;
		filho_do_irmao -> cor = NEGRO;
		
		//atualiza o ponteiro do irmão
		irmao = &filho_do_irmao;
		//Analiza outros possíveis casos
		Estudo_de_caso (pai, irmao, avo, Arvore, a);
	}
	else{
		filho_do_irmao = (*irmao) -> dir;
		//ROTAÇÃO PARA ESQUERDA

		(*irmao) -> dir = filho_do_irmao -> esq;
		filho_do_irmao -> esq = (*irmao);
		(*pai) -> esq = filho_do_irmao;
		//ATUALIZAR AS CORES

		(*irmao) -> cor = RUBRO;
		filho_do_irmao -> cor = NEGRO;
		
		//atualiza o ponteiro do irmão
		irmao = &filho_do_irmao;
		//Analiza outros possíveis casos
		Estudo_de_caso (pai, irmao, avo, Arvore, a);
	}
}


//Caso 4 da Remoção
void caso_4 (no **pai, no **irmao, no **avo, no **Arvore, int *a){
	//Primeiro faz a troca de cores do pai e do irmao
	//e depois verifica os casos da diereita e esquerda
	(*irmao) -> cor = (*pai) -> cor;
	(*pai) -> cor = NEGRO;
	if ((*pai) -> dir == (*irmao)){	//Quando o irmao é filho à direita do pai
		(*irmao) -> dir -> cor = NEGRO;
		//ROTAÇÃO PARA ESQUERDA
		(*pai) -> dir = (*irmao) -> esq;
		(*irmao) -> esq = (*pai);
	}
	else{
		(*irmao) -> esq -> cor = NEGRO;
		//ROTAÇÃO PARA DIREITA
		(*pai) -> esq = (*irmao) -> dir;
		(*irmao) -> dir  = (*pai);
	}
	//Atualiza o nó raiz
	if ((*Arvore) == (*pai)){	
		pai = irmao;
		(*Arvore) = (*pai);
	}
	else{
		if ((*avo) -> esq == (*pai)){	//Atualiza o ponteiro do avô
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
	while (aux -> esq != externo){ //percorre até o elemento mais à esquerda da árvore
		//(*pai) = aux;
		aux = aux -> esq;
	}
	return aux;
}

//Função de Remoção do nó
void remove_no (int valor, no **pt, no **pai, no **avo, no **Arvore, int *a){
	// Verifica logo se a Árvore está vazia ou se o elemento existe nela
	if ((*pt) == externo){
		printf ("Propriedade n%co existente.\n", atil);
	}
	else{
		if ((*pt) -> codigo == valor){ //Acha e remove o nó
			if ((*pt) -> dir != externo){
				no *suc = sucessor (pt); //procura o sucessor.
				
				//Troca as informações
				(*pt) -> codigo = suc -> codigo;
				(*pt) ->  informacao = suc -> informacao;
				//Depois que troca as informações com o sucessor,
				//procura o sucessor para removê-lo.
				
				remove_no (suc -> codigo, &((*pt) -> dir), pt, pai, Arvore, a);
			}
			else{ //Quando não tem sucessor à direita
				no *temp;
				
				printf ("Cadastro exclu%cdo com sucesso.\n", iagudo);
				if ((*pt) -> cor == RUBRO){ //Se o nó for Rubro, simplesmente desaloca ele.
					free ((*pt));
					(*pt) = externo;
				}
				else{ //Quando o nó é Negro
					//Vê se o nó pt é filho à direita ou à esquerda.
					no *irmao;
					//Se for o nó raiz, nao precisa verificar o pai.
					if ((*pt) != (*Arvore)){
					   /*Se o nó PT for filho       Irmao se torna filho    Senão Irmao se torna filho
					   à esquerda do pai             à direita do pai        à esquerda do pai */
						((*pai) -> dir == (*pt)) ? (irmao = (*pai) -> esq) : (irmao = (*pai) -> dir);
					}
					temp = (*pt) -> esq;	//referencia o filho à esquerda, remove o nó.
					free ((*pt));
					(*pt) = temp;
					(*pt) -> cor = NEGRO;	//O filho pega a cor do nó anterior
					
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
					/*Se o nó PT for filho       Irmao se torna filho    Senão Irmao se torna filho
					à direita do pai             à esquerda do pai        à direita do pai */
					((*pai) -> dir == (*pt)) ? (irmao = (*pai) -> esq) : (irmao = (*pai) -> dir);
					Estudo_de_caso (pai, &irmao, avo, Arvore, a);
				}
			}
			else{
				remove_no (valor, &((*pt) -> dir), pt, pai, Arvore, a);
				if ((*a) == 1){
					/*Se o nó PT for filho       Irmao se torna filho    Senão Irmao se torna filho
					à direita do pai             à esquerda do pai        à direita do pai */
					((*pai) -> dir == (*pt)) ? (irmao = (*pai) -> esq) : (irmao = (*pai) -> dir);
					Estudo_de_caso (pai, &irmao, avo, Arvore, a);
				}
			}
		}
	}
	(*Arvore) -> cor = NEGRO;
}

