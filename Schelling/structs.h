#ifndef STRUCTS_H
#define	STRUCTS_H

typedef struct elemento{
	char tipo;			// Tipo de elemento
	int sat;			// % de Satisfação 
	int vizV;			// Vizinhos Vazios
	int vizO;			// Vizinhos O
	int vizX;			// Vizinhos X
	int vizK;			// Vizinhos K
	int vizTotal;		// Total de Vizinhos excluindo os Vazios
	int deslocado;		// Já foi deslocado na corrente iteração???
	int seguido;		// Elemento seguido???
}elem;

typedef struct seguidos elemSeguidos, *pelemSeguidos;

struct seguidos {
	int coordO, coordX, coordK;
	pelemSeguidos prox;
};

typedef struct configuracao config, *pconfig;

struct configuracao {
	int nlin, ncol, pops, nAgentes, viz, fro, satO, satX, satK, des, iter;
	pconfig prox;
};

#endif	/* STRUCTS_H */