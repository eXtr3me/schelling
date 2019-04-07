#ifndef LISTAS_H
#define	LISTAS_H

// Prototipos das funções dos elementos seguidos

int lista_vazia(pelemSeguidos p);
void mostra_info(pelemSeguidos p);
pelemSeguidos insere_inicio(pelemSeguidos p, int O, int X, int K);
pelemSeguidos insere_final(pelemSeguidos p, int O, int X, int K);
void preenche(pelemSeguidos p, int O, int X, int K);
void liberta_lista(pelemSeguidos p);
void guarda_dados_txt(pelemSeguidos p, int ncol);



// Prototipos das funções de configuração

int lista_vazia_conf(pconfig p);
pconfig insere_final_conf(pconfig p, int nlin, int ncol, int pops, int nAgentes, int viz, int fro, int satO, int satX, int satK, int des, int iter);
void preenche_conf(pconfig p, int nlin, int ncol, int pops, int nAgentes, int viz, int fro, int satO, int satX, int satK, int des, int iter);
void guarda_dados_conf_txt(pconfig p);

// Prototipos das Funções para guardar ambiente

void grava_ambiente(elem *amb, int dimAmbiente, int nlin, int ncol, int pops, int nAgentes, int viz, int fro, int satO, int satX, int satK, int des, int iter);
void recupera_conf(int *nlin, int *ncol, int *pops, int *nAgentes, int *viz, int *fro, int *satO, int *satX, int *satK, int *des, int *iter);
void recupera_ambiente(elem *amb, int dimAmbiente);

#endif	/* LISTAS_H */