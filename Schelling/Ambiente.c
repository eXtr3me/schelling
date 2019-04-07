#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "structs.h"


int calcAgentes(int nlin, int ncol, double percentagem, int tipo){
	int result;
	result = (int)((nlin * ncol * percentagem) / tipo);
	return result;
}

void configurarAmbiente(int *nlin, int *ncol, int *pops, int *nAgentes, int *viz, int *fro, int *satO, int *satX, int *satK, int *des, int *iter){
	
	int minAgentes, maxAgentes, tipoSat;
	
        printf("\nDimensäes do Ambiente:\n\n");
	
	do {
		printf("\n\tLinhas (8 a 15): ");
		scanf("%d", nlin);
		fflush(stdin);
	} while (*nlin < 8 || *nlin > 15);
	
	do{
		printf("\n\tColunas (15 a 30): ");
		scanf("%d", ncol);
		fflush(stdin);
	} while (*ncol < 15 || *ncol > 30);
	
	do {
                printf("\n\nPopulacäes (2 ou 3): ");
		scanf("%d", pops);
		fflush(stdin);
	} while (*pops < 2 || *pops > 3);

	// Cálculo dos valores minimos e máximos de agentes por população
	minAgentes = calcAgentes(*nlin, *ncol, 0.5, *pops);
	maxAgentes = calcAgentes(*nlin, *ncol, 0.7, *pops);

	do {
                printf("\n\nAgentes por popula‡Æo (min: %d max: %d): ", minAgentes, maxAgentes);
		scanf("%d", nAgentes);
		fflush(stdin);
	} while (*nAgentes < minAgentes || *nAgentes > maxAgentes);
	
	do {
                printf("\n\nTipo de Vizinhan‡a (1 - Von Neumann | 2 - Moore): ");
		scanf("%d", viz);
		fflush(stdin);
	} while (*viz < 1 || *viz > 2);
	
	do {
		printf("\n\nIntroduza o tipo de Fronteira (1- Fechada | 2 - Toroidal): ");
		scanf("%d", fro);
		fflush(stdin);
	} while (*fro < 1 || *fro > 2);
	
	do {
        puts("\nTipo de satisfa‡Æo (1 - Geral | 2 - Por tipo de Agente): ");
		scanf("%d", &tipoSat);
		fflush(stdin);
	} while (tipoSat < 1 || tipoSat > 2);
		
		if (tipoSat == 1) {
			do {
                                printf("\n\n\tSatisfa‡Æo Geral (%%): ");
				scanf("%d", satO);
				fflush(stdin);
			} while (*satO < 0 || *satO > 100);
			*satX = *satK = *satO;
		}
		if (tipoSat == 2){
			do {
                                printf("\n\n\tSatisfa‡Æo para a Popula‡Æo O: ");
				scanf("%d", satO);
				fflush(stdin);
			} while (*satO < 0 || *satO > 100);
			do {
                                printf("\n\n\tSatisfa‡Æo para a Popula‡Æo X: ");
				scanf("%d", satX);
				fflush(stdin);
			} while (*satX < 0 || *satX > 100);
			if (*pops == 3) {
				do {
                                        printf("\n\n\tSatisfa‡Æo para a Popula‡Æo K: ");
					scanf("%d", satK);
					fflush(stdin);
				} while (*satK < 0 || *satK > 100);
			}
		}
	do {
                printf("\n\nDeslocamento dos Agentes (1 - C‚lula + Pr¢xima | 2 - Aleat¢rio): ");
		scanf("%d", des);
		fflush(stdin);
	} while (*des <1 || *des > 2);
	do {
                printf("\n\nM ximo de Itera‡äes: ");
		scanf("%d", iter);
		fflush(stdin);
	} while (*iter < 0 || *iter > 65535);
}

void gerarElementos(elem *amb, int tamAmbiente, int nElementos, char tipo){
	int elemento;
	srand((unsigned)time(NULL));
	while (nElementos > 0) {
		elemento = rand() % tamAmbiente;
		if (amb[elemento].tipo == ' ') {
			amb[elemento].tipo = tipo;
			nElementos--;
		}
	}
}

// Função para calcular a satisfação
int calculaSat(elem *amb, int nElementos, int satO, int satX, int satK){
	int i;
	int todosSatisfeitos = 1;
	for (i = 0; i < nElementos; i++){
		if (amb[i].vizTotal != 0){
			if (amb[i].tipo == 'O')
				amb[i].sat = amb[i].vizO * 100 / amb[i].vizTotal;
			if (amb[i].tipo == 'X')
				amb[i].sat = amb[i].vizX * 100 / amb[i].vizTotal;
			if (amb[i].tipo == 'K')
				amb[i].sat = amb[i].vizK * 100 / amb[i].vizTotal;
		}
		if (amb[i].tipo == 'O' && amb[i].sat < satO)
			todosSatisfeitos = 0;
		if (amb[i].tipo == 'X' && amb[i].sat < satX)
			todosSatisfeitos = 0;
		if (amb[i].tipo == 'K' && amb[i].sat < satK)
			todosSatisfeitos = 0;
	}
	return todosSatisfeitos;
}

// Inicializar as variáveis do Ambiente

void initAmbiente(elem *amb, int dimAmbiente){
	for (int i = 0 ; i < dimAmbiente ; i++){
		amb[i].tipo = ' ';
		amb[i].sat = 0;
		amb[i].vizK = 0;
		amb[i].vizO = 0;
		amb[i].vizTotal = 0;
		amb[i].vizV = 0;
		amb[i].vizX = 0;
		amb[i].deslocado = 0;
		amb[i].seguido = 0;
	}
}

// Desenhar o Ambiente

void desenharAmbiente(elem *amb, int nlinhas, int ncolunas, int satO, int satX, int satK){
	int elemento = 0;
	for (int i = 0 ; i < nlinhas ; i++){
		for (int j = 0; j < ncolunas; j++)
			printf("|%c", amb[elemento++].tipo);
		printf("|");
		elemento -= ncolunas;
		printf(" * ");
		for (int k = 0; k < ncolunas; k++){
			if (amb[elemento].tipo != ' ')
				printf("|%3d", amb[elemento++].sat);
			else {
				printf("|   ");
				elemento++;
			}
		}
		printf("|");
		elemento -= ncolunas;
		printf(" * ");
		for (int l = 0; l < ncolunas; l++){
			if (amb[elemento].tipo == ' ')
				printf("| ");
			if (amb[elemento].tipo == 'O'){
				if (amb[elemento].sat < satO)
					printf("|I");
				if (amb[elemento].sat >= satO)
					printf("|S");
			}
			if (amb[elemento].tipo == 'X'){
				if (amb[elemento].sat < satX)
					printf("|I");
				if (amb[elemento].sat >= satX)
					printf("|S");
			}
			if (amb[elemento].tipo == 'K'){
				if (amb[elemento].sat < satK)
					printf("|I");
				if (amb[elemento].sat >= satK)
					printf("|S");
			}
			elemento++;
		}
		printf("|\n");
	}
}

void satisfacaoPops(elem *amb, int dimAmbiente, int pops, int nAgentes, int satO, int satX, int satK){
	int elemento = 0;
	int perSatTotal, perSatO, perSatX, perSatK;
	int satisfeitosO, satisfeitosX, satisfeitosK;
	
	satisfeitosO = satisfeitosX = satisfeitosK = 0;

	for (int i = 0; i < dimAmbiente; i++){
		if (amb[elemento].tipo == 'O' && amb[elemento].sat >= satO)
			satisfeitosO++;
		if (amb[elemento].tipo == 'X' && amb[elemento].sat >= satX)
			satisfeitosX++;
		if (amb[elemento].tipo == 'K' && amb[elemento].sat >= satK)
			satisfeitosK++;
		elemento++;
	}
	
	perSatTotal = ((satisfeitosO + satisfeitosX + satisfeitosK) * 100) / (nAgentes * pops);
	perSatO = (satisfeitosO * 100) / nAgentes;
	perSatX = (satisfeitosX * 100) / nAgentes;
	perSatK = (satisfeitosK * 100) / nAgentes;
	printf("\nPercentagem de Satisfação Geral: %8d%%\n", perSatTotal);
	printf("Elementos satisfeitos da população O: %3d%%\n", perSatO);
	printf("Elementos satisfeitos da população X: %3d%%\n", perSatX);
	if (pops == 3)
		printf("Elementos satisfeitos da população K: %3d%%\n", perSatK);
	satisfeitosO = satisfeitosX = satisfeitosK = 0;
}