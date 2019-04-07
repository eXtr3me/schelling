#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "listas.h"


// Código para listas de elementos seguidos

// verificar se a lista está vazia
int lista_vazia(pelemSeguidos p){
	if (p == NULL)
		return 1;
	else
		return 0;
}

//mostar conteudo da lista
void mostra_info(pelemSeguidos p)
{
	while (p != NULL)
	{
		printf("%d\t%d\t%d\n",
			p->coordO, p->coordX, p->coordK);
		p = p->prox;
	}
}

// insere no inicio da lista
pelemSeguidos insere_inicio(pelemSeguidos p, int O, int X, int K){
	pelemSeguidos novo;
	if ((novo = malloc(sizeof(elemSeguidos))) == NULL)
		printf("Erro na alocacao de memoria\n");
	else {
		preenche(novo, O, X, K);
		novo->prox = p;
		p = novo;
	}
	return p;
}


// inserir no fim da lista
pelemSeguidos insere_final(pelemSeguidos p, int O, int X, int K){
	pelemSeguidos novo, aux;
	novo = malloc(sizeof(elemSeguidos));
	if (novo == NULL) {
		printf("\nErro na alocação de memória\n");
		return p;
	}
	if (p == NULL)
		p = novo;
	else {
		aux = p;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}
	preenche(novo, O, X, K);
	return p;
}

// Escrever valores numa lista
void preenche(pelemSeguidos p, int O, int X, int K){
	
	p->coordO = O;
	p->coordX = X;
	p->coordK = K;
	p->prox = NULL;
}

// libertar a memória de uma lista
void liberta_lista(pelemSeguidos p){
	pelemSeguidos aux;

	while (p != NULL){
		aux = p;
		p = p->prox;
		free(aux);
	}
}



void guarda_dados_txt(pelemSeguidos p, int ncol){
	int i = 0;
	FILE *f;
	f = fopen("data/report.txt", "w");
	if (f == NULL)
		return;
	while (p != NULL){
		fprintf(f, "Iter %2d:\t", i++);
		fprintf(f, "O: [%d][%d]\tX: [%d][%d]\tK: [%d][%d]\t\n", p->coordO / ncol, p->coordO % ncol, p->coordX / ncol, p->coordX % ncol, p->coordK / ncol, p->coordK % ncol);
		p = p->prox;
	}
	fclose(f);
}


// Código para listas de configurações

int lista_vazia_conf(pconfig p){
	if (p == NULL)
		return 1;
	else
		return 0;
}

pconfig insere_final_conf(pconfig p, int nlin, int ncol, int pops, int nAgentes, int viz, int fro, int satO, int satX, int satK, int des, int iter){
	pconfig novo, aux;
	novo = malloc(sizeof(config));
	if (novo == NULL) {
		printf("\nErro na alocação de memória\n");
		return p;
	}
	if (p == NULL)
		p = novo;
	else {
		aux = p;
		while (aux->prox != NULL)
			aux = aux->prox;
		aux->prox = novo;
	}
	preenche_conf(novo, nlin, ncol, pops, nAgentes, viz, fro, satO, satX, satK, des, iter);
	return p;
}

void preenche_conf(pconfig p, int nlin, int ncol, int pops, int nAgentes, int viz, int fro, int satO, int satX, int satK, int des, int iter){

	p->nlin = nlin;
	p->ncol = ncol;
	p->pops = pops;
	p->nAgentes = nAgentes;
	p->viz = viz;
	p->fro = fro;
	p->satO = satO;
	p->satX = satX;
	p->satK = satK;
	p->des = des;
	p->iter = iter;
	p->prox = NULL;
}

void guarda_dados_conf_txt(pconfig p){
	int i = 0;
	FILE *f;
	f = fopen("data/report.txt", "a");
	if (f == NULL)
		return;
	while (p != NULL){
		fprintf(f, "Iter %2d:\t", i++);
		fprintf(f, "\n\nDIM: %d %d\nPOPS: %d\nDIM_POP: %d\nVIZ: %d\nFRONTEIRA: %d\nK: %d %d %d\nMOVE: %d\nNUM_ITER: %d\n", p->nlin, p->ncol, p->pops, p->nAgentes, p->viz, p->fro, p->satO, p->satX, p->satK, p->des, p->iter);
		p = p->prox;
	}
	fclose(f);
}

// Guardar ambiente em ficheiro Binário

// Gravar em ficheiro binário
void grava_ambiente(elem *amb, int dimAmbiente, int nlin, int ncol, int pops, int nAgentes, int viz, int fro, int satO, int satX, int satK, int des, int iter){
	FILE *f;
	f = fopen("data/ambiente.dat", "wb");
	if (f == NULL) {
		printf("Erro ao criar ficheiro\n");
		return;
	}
	else {
		fwrite(&nlin, sizeof(int), 1, f);
		fwrite(&ncol, sizeof(int), 1, f);
		fwrite(&pops, sizeof(int), 1, f);
		fwrite(&nAgentes, sizeof(int), 1, f);
		fwrite(&viz, sizeof(int), 1, f);
		fwrite(&fro, sizeof(int), 1, f);
		fwrite(&satO, sizeof(int), 1, f);
		fwrite(&satX, sizeof(int), 1, f);
		fwrite(&satK, sizeof(int), 1, f);
		fwrite(&des, sizeof(int), 1, f);
		fwrite(&iter, sizeof(int), 1, f);
		for (int i = 0 ; i < dimAmbiente ; i++){
			fwrite(&amb[i].tipo, sizeof(char), 1, f);
		}
		fclose(f);
	}
}

void recupera_conf(int *nlin, int *ncol, int *pops, int *nAgentes, int *viz, int *fro, int *satO, int *satX, int *satK, int *des, int *iter){
	FILE *f;
	f = fopen("data/ambiente.dat", "rb");
	if (!f)
		printf("Erro ao abrir ficheiro");
	fread(nlin, sizeof(int), 1, f);
	fread(ncol, sizeof(int), 1, f);
	fread(pops, sizeof(int), 1, f);
	fread(nAgentes, sizeof(int), 1, f);
	fread(viz, sizeof(int), 1, f);
	fread(fro, sizeof(int), 1, f);
	fread(satO, sizeof(int), 1, f);
	fread(satX, sizeof(int), 1, f);
	fread(satK, sizeof(int), 1, f);
	fread(des, sizeof(int), 1, f);
	fread(iter, sizeof(int), 1, f);
	fclose(f);
}

void recupera_ambiente(elem *amb, int dimAmbiente){
	FILE *f;
	f = fopen("data/ambiente.dat", "rb");
	if (!f)
		printf("Erro ao abrir ficheiro");
	fseek(f, sizeof(int)* 11, SEEK_SET);
	for (int i = 0; i < dimAmbiente; i++)
		fread(&amb[i].tipo, sizeof(char), 1, f);
}