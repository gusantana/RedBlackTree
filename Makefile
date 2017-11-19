CC = gcc
STD = -std=c99
SAVE = -S

#Header da estrutura da árvore##
ARN = Arvore_Rubro_Negra
HEADER1 = $(ARN).c $(ARN).h

#Header dos menus para o Principal##
MENUS = AplicacaoRN
HEADER2= $(MENUS).c $(MENUS).h
MAIN = Principal


#Nome do executável
TRAB = "Arvore Rubro Negra"

#Arquivos Objetos
OBJ = $(MAIN).o $(ARN).o $(MENUS).o
CLEAN = rm -f *.o *.gch


all: projeto headers
	$(CC) $(STD) -o $(TRAB) $(OBJ)

headers: $(HEADER1) $(HEADER2)
	$(CC) $(STD) -c $(HEADER1)
	$(CC) $(STD) -c $(HEADER2)

projeto: $(MAIN).c
	$(CC) $(STD) -c $(MAIN).c

clean: 
	$(CLEAN)