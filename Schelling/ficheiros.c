#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

// Ler ficheiro de configuração

void lerFicheiroConf(int *nlin, int *ncol, int *pops, int *nAgentes, int *viz, int *fro, int *satO, int *satX, int *satK, int *des, int *iter){
	FILE *confFile;
	char lixo[50];
	char path[50] = "data/";
	char *ext = ".txt";
	char filename[50];
	printf("Introduza o nome do ficheiro a abrir: ");
	scanf("%s", &filename);
	strcat(filename, ext);
	strcat(path, filename);
	confFile = fopen(path, "r");
	if (confFile != NULL){
		fscanf(confFile, "%s%d%d", &lixo, nlin, ncol);
		fscanf(confFile, "%s %d", &lixo, pops);
		fscanf(confFile, "%s %d", &lixo, nAgentes);
		fscanf(confFile, "%s %d", &lixo, viz);
		fscanf(confFile, "%s %d", &lixo, fro);
		if (*pops == 2)
			fscanf(confFile, "%s %d %d", &lixo, satO, satX);
		if (*pops == 3)
			fscanf(confFile, "%s %d %d %d", &lixo, satO, satX, satK);
		fscanf(confFile, "%s %d", &lixo, des);
		fscanf(confFile, "%s %d", &lixo, iter);
		fclose(confFile);
	}
}

// Escrever Ficheiro de configuração

void escreverFicheiroConf(){
	FILE *confFile;
	confFile = fopen("data/config1.txt", "w");
	if (confFile != NULL)
		puts("Ficheiro aberto em modo de escrita");
	fclose(confFile);
}