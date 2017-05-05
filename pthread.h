//JOAN ANDRES CAICEDO AYALA 201627015 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Número de hilos a crear
int MAXTHREAD= 50;

// Funcion para imprimir hola n, con n=Identificador
void* worktodo(void* arg) {
        int o;
        o=pthread_self();
        printf("Hola %d\n",o);         
        return 0;
}

int main(int argc, char** argv) {
        int i; // Variable para los fork
        pthread_t ptarray[MAXTHREAD]; // almacena 'id' de hilos
        int count = 0;

        // Se crean los hilos
        for (i = 0; i < MAXTHREAD; i++) {
                pthread_create(&ptarray[i],NULL, worktodo, NULL);
        }

        // Se espera por la terminacion de cada hilo
        for (i = 0; i < MAXTHREAD; i++) {
                pthread_join(ptarray[i],NULL);
                count += 1; // Contador del númeor de hilos que hicieron el trabajo
        }
        printf("\nTotal HILOS %d\n", count);
}

