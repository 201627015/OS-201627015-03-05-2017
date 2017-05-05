
#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define MAXRECT 1000000
#define MAXTHREAD 10
#define BASE 0.0
#define LIMIT 1.0

double length = LIMIT - BASE; // La longitud en el eje 'x'
double numRectxThread = (double)(MAXRECT/MAXTHREAD); // Cuantos hilos/rectangulo
double base_length = 0; // Variable que tiene el ancho de cada rectangulo
double sumTotal = 0; // Variable que tendra la suma total
double partialSums[MAXTHREAD]; // Variable que tien la suma parcial de c/hilo

// Funcion a la que se le calculara la integral, x^2
double function(double x) {
	return x * x; 
}
void* calcular(void *arg) {
	// 1- Identificar que porcion de rectangulos le toca procesar a este 
	//    hilo. Eso ira en la variable 'arg'. Cree una variable 'id' para
	//    esto.
	int id = (int)arg;
//      (id*numRectxTheread + numRectxTheread)/(MAXRECT);
	// 2- Identificar ademas en que posicion del eje 'x' se empieza a
	//    calcular el area bajo la curva de los rectangulos. Llame a esta
	//    variable 'loslimit'
	int loslimit=(id*numRectxThread)/(MAXRECT);
	// 3- Inicializar la posicion del vector que le corresponde a este hilo,
	//    'partialSums' a cero. Recuerde que la variable 'id' del item 1
	//    le indica que posicion en el vector le corresponde a este hilo.
	partialSums[id]=0;
	// 4- Escriba un ciclo que debe recorrer el segmento de 'x' que le 
	//    corresponde a este hilo y donde calcula el area de los rectangulos
        //    que se encuentran en este segmento. Recuerde que la variable
	//    'numRectxThread' contiene el numero de rectangulos que debe
        //    procesar cada hilo.
	int i;
	int val;
	int other;
	for (i= loslimit*10; i<loslimit +numRectxThread ; i++){
	partialSums[id]+= (function(i)*base_length/10000000000);
	}
	// 5- El area de cada rectangulo se calcula con 
	printf("sum: %lf\n", partialSums[id]);
	pthread_exit(NULL);
}

int main(int argc, char** argv) {
	pthread_t identi[MAXTHREAD];
	long identiH[MAXTHREAD];
	long taskids[MAXTHREAD];
	base_length = length/MAXRECT; // esta variable contiene el ancho de
				      // cada base de cada rectangulo
	printf("base length: %lf numRectxThread: %lf\n",base_length, numRectxThread);

	// Creacion de los hilos que calcularan el area bajo la curva
	for (int i = 0; i < MAXTHREAD; i++) {
		taskids[i] =(long) i;
		identiH[i]=pthread_create(&identi[i], NULL, calcular, (void*)taskids[i]);
	}
	// Ciclo donde se espera el resultado de cada hilo
	for (int i = 0; i < MAXTHREAD; i++) {
		pthread_join(identi[i], NULL);
		sumTotal += partialSums[i];
	}
	printf("Suma total %lf\n",sumTotal); 
	pthread_exit(NULL);
}
