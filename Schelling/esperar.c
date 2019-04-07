#include <time.h>
// Suspende a execução do programa durante aproximadamente seg segundos
void espera(int seg) {
	time_t inicio = time(NULL);
	long int i;
	do{
		for (i = 0; i<100000; i++)
			;
	} while (difftime(time(NULL), inicio) < seg);
}