#ifndef DESLOCAR_H
#define	DESLOCAR_H

int deslocar(elem *amb, int coordVerificar, int coordenadaAmb);
void deslocarInsatisfeitos(elem *amb, int nlin, int ncol, int fro, int viz, int satO, int satX, int satK, int des, int *deslocadosO, int *deslocadosX, int *deslocadosK);

#endif	/* DESLOCAR_H */