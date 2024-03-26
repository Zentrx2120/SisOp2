/*  Absalon Cortes Sebastian
    18 de marzo 2024
    version 1.00
    Practica 3 Algoritmo FCFS
*/

#include <stdio.h> //Entrada y salida
#include <pthread.h> //Libreria para crear hilos

#define Tamanio 3 //El numero de procesos

typedef struct{ //Componentes del proceso
    int id;
    char nom[15];
} Proceso;

void ejecucion(void *arg){ //Funcion de ejecucion del .bat
    Proceso *proceso = (Proceso *)arg;
    system(proceso->nom);
    printf("El proceso con id %d se a ejecutado.\n", proceso->id);
    pthread_exit(NULL);
};

int main(){
    int x;
    pthread_t hilos[Tamanio];
    Proceso hilo[Tamanio]={//Procesos
        {1, "Cancion1.bat"},
        {2, "Cancion2.bat"},
        {3, "Cancion3.bat"}
    };

    for (int i = 0; i <= Tamanio; i++) {//Creacion de los procesos y asignacion de id por llegada
        if (pthread_create(&hilos[i], NULL, (void *) &ejecucion, (void *) &hilo[i]) != 0) {
            perror("pthread_create");
        }
        printf("Continuar\n1.-Si\n2.-No"); //Menu de continuacion
        scanf("%d",& x);
        if(x=1){
            printf("\n");
        }
        if(x=2){
            i=3;
        }
    }

    for (int i = 0; i < Tamanio; i++) {//Error al crear el hilo
        if (pthread_join(hilos[i], NULL) != 0) {
            perror("pthread_join");
        }
    }
 
    printf("Todos los procesos han terminado.\n");

    return 0;
}