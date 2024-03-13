#include <stdio.h>
#include <assert.h>
#include <pthread.h>

//Compilacion condicional
#define _DEBUG

void *IncrDecr(void *);

//La variable global y compartida
int x=0;

int main(int argc, char *argv[]){

    pthread_t t0id, t1id;

    pthread_create(&t0id, NULL, IncrDecr, NULL);
    pthread_create(&t1id, NULL, IncrDecr, NULL);
#ifdef _DEBUG
    printf("Hilos Creados\n");
    printf("Inicio de sonda de testeo\n");
#endif
    //sonda que comprueba el invariante
    while(1){
        assert(0<=x && x<=2); // Inv: 0<=x<=2
        printf("%2d", x);
    }
    //aqui nunca llega
}

//componente del multiprograma
void *IncrDecr(void *arg){
#ifdef _DEBUG
    printf("Hilo IncrDecr iniciado\n");
#endif
    for(;;){
        x = x+1;
        x = x-1;
    }
}