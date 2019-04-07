#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "structs.h"

void contarViz(elem *amb, int coordVerificar, int coordenadaAmb){
	if (amb[coordVerificar].tipo == ' ')
		amb[coordenadaAmb].vizV++;
	if (amb[coordVerificar].tipo == 'O')
		amb[coordenadaAmb].vizO++;
	if (amb[coordVerificar].tipo == 'X')
		amb[coordenadaAmb].vizX++;
	if (amb[coordVerificar].tipo == 'K')
		amb[coordenadaAmb].vizK++;
	amb[coordenadaAmb].vizTotal = amb[coordenadaAmb].vizO + amb[coordenadaAmb].vizX + amb[coordenadaAmb].vizK;		// Faz v�rias vezes a conta!!!!!! Desnecess�rio
}


// Procurar Vizinhos

void procurarViz(elem *amb, int nlin, int ncol, int fro, int viz){
	int coordenada = 0;																								// Representa a Coordenada na Matriz din�mica unidimensional
	int linha, coluna, coordVerificar;
	for (int i = 0; i < nlin; i++){
		for (int j = 0; j < ncol; j++){
			linha = coordenada / ncol;
			coluna = coordenada % ncol;
			amb[coordenada].vizK = amb[coordenada].vizO = amb[coordenada].vizV = amb[coordenada].vizX = 0;			// Zerar os vizinhos
			
			// Verifica��o em ambientes Toroidais
			if (fro == 2){
				// Verificar posic�o superior
				if (linha == 0){
					coordVerificar = coordenada + (ncol * (nlin - 1));
					contarViz(amb, coordVerificar, coordenada);
				}
				// Verificar posi��o inferior
				if (linha == (nlin - 1)){
					coordVerificar = coordenada - (ncol * (nlin - 1));
					contarViz(amb, coordVerificar, coordenada);
				}
				// Verificar posi��o esquerda
				if (coluna == 0){
					coordVerificar = coordenada + ncol - 1;
					contarViz(amb, coordVerificar, coordenada);
				}
				// Verificar posi��o direita
				if (coluna = ncol - 1) {
					coordVerificar = coordenada - ncol + 1;
					contarViz(amb, coordVerificar, coordenada);
				}
				// Verificar se for vizinhan�a de Moore (Diagonais)
				if (viz == 2){
					// Verificar diagonal superior Esquerda
					if (linha == 0 && coordenada != 0){
						coordVerificar = coordenada + (ncol * (nlin -1)) - 1 ;
						contarViz(amb, coordVerificar, coordenada);
					}
					// Verificar diagonal superior Direita
					if (linha == 0 && coordenada != ncol - 1) {
						coordVerificar = coordenada + (ncol * (nlin - 1)) + 1;
						contarViz(amb, coordVerificar, coordenada);
					}
					// Verificar diagonal inferior Esquerda
					if (linha < nlin - 1 && coluna > 0){
						coordVerificar = coordenada + ncol - 1;
						contarViz(amb, coordVerificar, coordenada);
					}
					// Verificar diagonal inferior Direita
					if (linha < nlin - 1 && coluna < ncol - 1){
						coordVerificar = coordenada + ncol + 1;
						contarViz(amb, coordVerificar, coordenada);
					}
				}
			}
			
			// Verifica��o em ambientes fechados e Toroidais
			if (fro >= 1){
				// Verificar posic�o superior
				if (linha > 0){
					coordVerificar = coordenada - ncol;
					contarViz(amb, coordVerificar, coordenada);
				}
				// Verificar posi��o inferior
				if (linha < (nlin - 1)){
					coordVerificar = coordenada + ncol;
					contarViz(amb, coordVerificar, coordenada);
				}
				// Verificar posi��o esquerda
				if (coluna > 0){
					coordVerificar = coordenada - 1;
					contarViz(amb, coordVerificar, coordenada);
				}
				// Verificar posi��o direita
				if (coluna < ncol - 1) {
					coordVerificar = coordenada + 1;
					contarViz(amb, coordVerificar, coordenada);
				}
				// Verificar se for vizinhan�a de Moore (Diagonais)
				if (viz == 2){
					// Verificar diagonal superior Esquerda
					if (linha > 0 && coluna > 0){
						coordVerificar = coordenada - ncol - 1;
						contarViz(amb, coordVerificar, coordenada);
					}
					// Verificar diagonal superior Direita
					if (linha > 0 && coluna < ncol - 1) {
						coordVerificar = coordenada - ncol + 1;
						contarViz(amb, coordVerificar, coordenada);
					}
					// Verificar diagonal inferior Esquerda
					if (linha < nlin - 1 && coluna > 0){
						coordVerificar = coordenada + ncol - 1;
						contarViz(amb, coordVerificar, coordenada);
					}
					// Verificar diagonal inferior Direita
					if (linha < nlin - 1 && coluna < ncol - 1){
						coordVerificar = coordenada + ncol + 1;
						contarViz(amb, coordVerificar, coordenada);
					}
				}
			}
			coordenada++;
		}
	}
}