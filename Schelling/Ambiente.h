#ifndef CRIARAMB_H
#define	CRIARAMB_H

int calcAgentes(int nlin, int ncol, double percentagem, int tipo);
void configurarAmbiente(int *nlin, int *ncol, int *pops, int *nAgentes, int *viz, int *fro, int *satO, int *satX, int *satK, int *des, int *iter);
void gerarElementos(elem *amb, int tamAmbiente, int nElementos, char tipo);
int calculaSat(elem *amb, int nElementos, int satO, int satX, int satK);
void initAmbiente(elem *amb, int dimAmbiente);
void desenharAmbiente(elem *amb, int nlinhas, int ncolunas, int satO, int satX, int satK);
void satisfacaoPops(elem *amb, int dimAmbiente, int pops, int nAgentes, int satO, int satX, int satK);

#endif	/* CRIARAMB_H */