#include <stdio.h>
#include "structs.h"
#include <time.h>
#include <stdlib.h>
#include "listas.h"

void escolherSeguidos(elem *amb, int dimAmbiente, int pops, int ncolunas, int *seguidoO, int * seguidoX, int *seguidoK){
	int encontrado = 0;
	int elemento;
	*seguidoO = *seguidoX = *seguidoK = -1;
	srand((unsigned)time(NULL));
	do {
		elemento = rand() % dimAmbiente;
		if (amb[elemento].tipo == 'O'){
			*seguidoO = elemento;
			amb[elemento].seguido = 1;
			encontrado = 1;
		}
	} while (encontrado != 1);
	encontrado = 0;
	do {
		elemento = rand() % dimAmbiente;
		if (amb[elemento].tipo == 'X'){
			*seguidoX = elemento;
			amb[elemento].seguido = 1;
			encontrado = 1;
		}
	} while (encontrado != 1);
	encontrado = 0;
	if (pops == 3){
		do {
			elemento = rand() % dimAmbiente;
			if (amb[elemento].tipo == 'K'){
				*seguidoK = elemento;
				amb[elemento].seguido = 1;
				encontrado = 1;
			}
		} while (encontrado != 1);
	}
	printf("\nElementos seguidos:\n\n\tO: [%d][%d]\tX: [%d][%d]", *seguidoO / ncolunas, *seguidoO % ncolunas,  *seguidoX / ncolunas, *seguidoX % ncolunas);
	if (pops == 3)
		printf("\tK: [%d][%d]\n", *seguidoK / ncolunas, *seguidoK % ncolunas);	
}