#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "structs.h"

int deslocar(elem *amb, int coordVerificar, int coordenadaAmb){
	if (amb[coordVerificar].tipo == ' '){
		amb[coordVerificar].tipo = amb[coordenadaAmb].tipo;
		amb[coordenadaAmb].tipo = ' ';
		amb[coordVerificar].deslocado = 1;
		if (amb[coordenadaAmb].seguido == 1){
			amb[coordenadaAmb].seguido = 0;
			amb[coordVerificar].seguido = 1;
		}
		return 1;
	}
	return 0;
}

void deslocarInsatisfeitos(elem *amb, int nlin, int ncol, int fro, int viz, int satO, int satX, int satK, int des, int *deslocadosO, int *deslocadosX, int *deslocadosK){
	int coordenada = 0;
	int linha, coluna, coordVerificar;
	int sat;											// Satisfação a comparar consoante o tipo de elemento.
	for (int i = 0; i < nlin; i++){
		for (int j = 0; j < ncol; j++){
			linha = coordenada / ncol;
			coluna = coordenada % ncol;
			// Determinar o valor de sat
			if (amb[coordenada].tipo == 'O')
				sat = satO;
			if (amb[coordenada].tipo == 'X')
				sat = satX;
			if (amb[coordenada].tipo == 'K')
				sat = satK;
			// Deslocar se a coordenada não for uma casa vazia & se a satisfação for menor que a definida para o seu tipo de elemento & se nao tiver sido ainda deslocado
			if (amb[coordenada].tipo != ' ' && amb[coordenada].sat < sat && amb[coordenada].deslocado == 0){
				int deslocado = 0;
				if (des == 1){
					// Deslocamento em ambientes fechados
					if (fro >= 1){
						int distancia = 0;
						do {
							distancia++;
							
							// Tentar deslocar para posição superior
							if (linha - distancia >= 0 && amb[coordenada].deslocado == 0){
								coordVerificar = coordenada - ncol * distancia;
								deslocar(amb, coordVerificar, coordenada);
								deslocado = 1;
							}
							
							// Tentar deslocar para diagonal superior Direita
							if (linha - distancia >= 0 && coluna + distancia <= ncol - 1 && amb[coordenada].deslocado == 0) {
								coordVerificar = coordenada - ncol * distancia + 1;
								deslocar(amb, coordVerificar, coordenada);
							}
							
							// Tentar deslocar para posição esquerda
							if (coluna - distancia >= 0 && amb[coordenada].deslocado == 0){
								coordVerificar = coordenada - distancia;
								deslocar(amb, coordVerificar, coordenada);
								deslocado = 1;
							}
							
							// Tentar deslocar para diagonal inferior Direita
							if (linha + distancia <= nlin - 1 && coluna + distancia <= ncol - 1 && amb[coordenada].deslocado == 0){
								coordVerificar = coordenada + ncol * distancia + 1;
								deslocar(amb, coordVerificar, coordenada);
							}
							
							// Tentar deslocar para diagonal inferior Esquerda
							if (linha + distancia <= nlin - 1 && coluna - distancia >= 0 && amb[coordenada].deslocado == 0){
								coordVerificar = coordenada + ncol * distancia - 1;
								deslocar(amb, coordVerificar, coordenada);
							}

							// Tentar deslocar para posição direita
							if (coluna + distancia <= ncol - 1 && amb[coordenada].deslocado == 0) {
								coordVerificar = coordenada + distancia;
								deslocar(amb, coordVerificar, coordenada);
								deslocado = 1;
							}
							
							// Tentar deslocar para diagonal superior Esquerda
							if (linha - distancia >= 0 && coluna - distancia >= 0 && amb[coordenada].deslocado == 0){
								coordVerificar = coordenada - ncol * distancia - 1;
								deslocar(amb, coordVerificar, coordenada);
							}
							
							// Tentar deslocar para posição inferior
							if (linha + distancia <= nlin - 1 && amb[coordenada].deslocado == 0){
								coordVerificar = coordenada + ncol * distancia;
								deslocar(amb, coordVerificar, coordenada);
								deslocado = 1;
							}
						} while (deslocado != 1);
					}

				}
				if (des == 2){
					srand((unsigned)time(NULL));
					do {
						coordVerificar = rand() % (nlin * ncol);
						deslocado = deslocar(amb, coordVerificar, coordenada);
					} while (deslocado != 1);
				}
				// Contar elementos deslocados
				if (amb[coordVerificar].tipo == 'O')
					(*deslocadosO)++;
				if (amb[coordVerificar].tipo == 'X')
					(*deslocadosX)++;
				if (amb[coordVerificar].tipo == 'K')
					(*deslocadosK)++;
			}
			coordenada++;
		}
	}
}