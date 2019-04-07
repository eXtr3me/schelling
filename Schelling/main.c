#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "Ambiente.h"
#include "verificar.h"
#include "ficheiros.h"
#include "deslocar.h"
#include "esperar.h"
#include "seguidos.h"
#include "listas.h"

int main(int argc, char** argv) {

	// Declara��o do Ambiente de Simula��o

	elem *ambiente;

	// Listas ligada

	pelemSeguidos lista = NULL;
	pconfig conf = NULL;
	
	// verificar se a listas est�o vazia
	
	if (lista_vazia(lista))
		printf("Lista Vazia\n");

	if (lista_vazia_conf(conf))
		printf("Lista Vazia\n");

	// Declara��o de Vari�veis
	int nlin, ncol, pops, nAgentes, viz, fro, satO, satX, satK, des, iter;
	int deslocadosO, deslocadosX, deslocadosK;
	int seguidoO, seguidoX, seguidoK;
	int dimAmbiente;
	int todosSatisfeitos = 0;
	int opcao;
	int modo;
	int opt;
	int tipoSat;
	int gerarElem = 0;
	int inter = 0;
	
	// Inicializa��o de variaveis

	deslocadosO = deslocadosX = deslocadosK = 0;
	seguidoO = seguidoX = seguidoK = 0;
	satO = satX = satK = 0;
	// Menu Principal
    
	printf("O Modelo de Segrega��o de Schelling\n\n\n");
	printf("Menu Principal:\n\n");
	printf("1 - Criar Ambiente\n");
    printf("2 - Carregar Configura��o de Ficheiro\n");
	printf("3 - Retomar Simula��o\n");
	printf("4 - Sair\n");
	
	do {
        printf("\nIntroduza a op��o pretendida: ");
		scanf("%d", &opcao);
		fflush(stdin);
		switch (opcao) {
			
		case 1:
			configurarAmbiente(&nlin, &ncol, &pops, &nAgentes, &viz, &fro, &satO, &satX, &satK, &des, &iter);	// Obter os dados de Configura��o da Simula��o
			gerarElem = 1;
			break;
			
		case 2:
			lerFicheiroConf(&nlin, &ncol, &pops, &nAgentes, &viz, &fro, &satO, &satX, &satK, &des, &iter);
			gerarElem = 1;
			break;
		
		case 3:
			recupera_conf(&nlin, &ncol, &pops, &nAgentes, &viz, &fro, &satO, &satX, &satK, &des, &iter);
			break;
		
		case 4:
			return (EXIT_SUCCESS);
			
		default:
                        printf("Op��o Inv�lida\n");
		}
	} while (opcao < 1 || opcao > 4);

	// Simular
	printf("\n\nDIM: %d %d POPS: %d nAGENTES: %d VIZ: %d FRO: %d SATO: %d SATX: %d SATK: %d DES: %d ITER: %d\n\n\n", nlin, ncol, pops, nAgentes, viz, fro, satO, satX, satK, des, iter);
	// preencher lista ligada com a configura��o
	conf = insere_final_conf(conf, nlin, ncol, pops, nAgentes, viz, fro, satO, satX, satK, des, iter);
	// guardar dados de configura��o em ficheiro de texto (Relat�rio)
	guarda_dados_conf_txt(conf);															// Calcular dimens�o do ambiente
	dimAmbiente = nlin * ncol;
	ambiente = (elem*)malloc(dimAmbiente * sizeof(elem));								// Aloca��o de Mem�ria dinamica para o Ambiente
	// Testar aloca��o de mem�ria
	if (ambiente == NULL){
		printf("Erro ao alocar mem�ria\n");
		return (EXIT_FAILURE);
	}
	initAmbiente(ambiente, dimAmbiente);												// Inicializar vari�veis do ambiente
	if (gerarElem == 1){
		gerarElementos(ambiente, dimAmbiente, nAgentes, 'X');								// Gerar elementos do tipo X
		gerarElementos(ambiente, dimAmbiente, nAgentes, 'O');								// Gerar elementos do tipo O
		if (pops == 3)
			gerarElementos(ambiente, dimAmbiente, nAgentes, 'K');							// Gerar elementos do tipo K
	}
	if (gerarElem == 0)
		recupera_ambiente(ambiente, dimAmbiente);
	procurarViz(ambiente, nlin, ncol, fro, viz);										// Analizar Vizinhos
	todosSatisfeitos = calculaSat(ambiente, dimAmbiente, satO, satX, satK);				// Verificar se est�o todos satisfeitos (Calcular Satisfa��o)
	desenharAmbiente(ambiente, nlin, ncol, satO, satX, satK);							// Desenhar o Ambiente
	putchar('\n');
	escolherSeguidos(ambiente, dimAmbiente, pops, ncol, &seguidoO, &seguidoX, &seguidoK);
	// guardar seguidos na lista ligada
	//lista = insere_inicio(lista, seguidoO, seguidoX, seguidoK);
	lista = insere_final(lista, seguidoO, seguidoX, seguidoK);
	do {
		printf("\nModo de execu��o (1- Passo a Passo | 2 - Sequencial): ");
		scanf("%d", &modo);
	} while (modo < 1 || modo > 2);
	while (iter > 0 && todosSatisfeitos != 1){
		deslocarInsatisfeitos(ambiente, nlin, ncol, fro, viz, satO, satX, satK, des, &deslocadosO, &deslocadosX, &deslocadosK);
		procurarViz(ambiente, nlin, ncol, fro, viz);									// Analizar Vizinhos
		todosSatisfeitos = calculaSat(ambiente, dimAmbiente, satO, satX, satK);			// Verificar se est�o todos satisfeitos (Calcular Satisfa��o)
		printf("\n");
		desenharAmbiente(ambiente, nlin, ncol, satO, satX, satK);
		satisfacaoPops(ambiente, dimAmbiente, pops, nAgentes, satO, satX, satK);
		// Imprimir o numero de elementos deslocados por tipo
		printf("\nDesO: %d\tDesX: %d\tDesK: %d\tDesTotal: %d\n", deslocadosO, deslocadosX, deslocadosK, deslocadosO + deslocadosX + deslocadosK);
		deslocadosO = deslocadosX = deslocadosK = 0;
		// Atualizar seguidos
		for (int i = 0; i < dimAmbiente; i++){
			if (ambiente[i].seguido == 1){
				if (ambiente[i].tipo == 'O')
					seguidoO = i;
				if (ambiente[i].tipo == 'X')
					seguidoX = i;
				if (ambiente[i].tipo == 'K')
					seguidoK = i;
			}
		}
		// guardar seguidos na lista ligada
		//lista = insere_inicio(lista, seguidoO, seguidoX, seguidoK);
		lista = insere_final(lista, seguidoO, seguidoX, seguidoK);
		for (int i = 0; i < dimAmbiente; i++)
			ambiente[i].deslocado = 0;
		iter--;
		printf("\nFaltam %d itera��es\n", iter);
		
		// Modo passo a passo!!! Alterar configura��es???
		if (modo == 1){
			printf("\nAlterar parametros? (1 - Sim | 2 - N�o): ");
			scanf("%d", &opt);
			switch (opt){
			case 1:
				do {
					puts("\nTipo de satisfa��o (1 - Geral | 2 - Por tipo de Agente): ");
					scanf("%d", &tipoSat);
					fflush(stdin);
				} while (tipoSat < 1 || tipoSat > 2);

				if (tipoSat == 1) {														// Satisfa��o geral
					do {
						printf("\n\n\tSatisfa��o Geral (%%): ");
						scanf("%d", &satO);
						fflush(stdin);
					} while (satO < 0 || satO > 100);
					satX = satK = satO;
				}
				if (tipoSat == 2){														// Satisfa��o por tipo de agente
					do {
						printf("\n\n\tSatisfa��o para a Popula��o O: ");
						scanf("%d", &satO);
						fflush(stdin);
					} while (satO < 0 || satO > 100);
					do {
						printf("\n\n\tSatisfa��o para a Popula��o X: ");
						scanf("%d", &satX);
						fflush(stdin);
					} while (satX < 0 || satX > 100);
					if (pops == 3) {
						do {
							printf("\n\n\tSatisfa��o para a Popula��o K: ");
							scanf("%d", &satK);
							fflush(stdin);
						} while (satK < 0 || satK > 100);
					}
				}
				do {
					printf("\n\nTipo de Vizinhan�a (1 - Von Neumann | 2 - Moore): ");
					scanf("%d", &viz);
					fflush(stdin);
				} while (viz < 1 || viz > 2);
				do {
					printf("\n\nDeslocamento dos Agentes (1 - C�lula + Pr�xima | 2 - Aleat�rio): ");
					scanf("%d", &des);
					fflush(stdin);
				} while (des <1 || des > 2);
				conf = insere_final_conf(conf, nlin, ncol, pops, nAgentes, viz, fro, satO, satX, satK, des, iter);
			case 2:
				break;
			}
			printf("Deseja interromper a simula��o? (1 - Sim | 2 - N�o): ");
			scanf("%d", &inter);
			if (inter == 1){
				grava_ambiente(ambiente, dimAmbiente, nlin, ncol, pops, nAgentes, viz, fro, satO, satX, satK, des, iter);			// guardar ambiente em ficheiro bin�rio
				return (EXIT_SUCCESS);
			}
		}
		if (modo == 2)																											// Se o modo for o sequencial!!!
			espera(0);
	}
	guarda_dados_txt(lista, ncol);																								// Guardar a rota dos seguidos
	guarda_dados_conf_txt(conf);
	free(ambiente);																												// Libertar a Mem�ria
	return (EXIT_SUCCESS);
}