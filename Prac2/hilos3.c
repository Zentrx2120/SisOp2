#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#define CAPACIDAD 16

void *set_buffer_to(void *);
void yield();

//las variables globales y compartidas
int buffer[CAPACIDAD];
pthread_mutex_t mutex;

int main(int argc, char *argv[]){
    pthread_t hilo0, hilo1;
    int val[2]={4,8};
    int i;

    for(i=0; i<CAPACIDAD; i++){
        buffer[i] = 0;
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&hilo0, NULL, set_buffer_to, (void *)&val[0]);
    pthread_create(&hilo1, NULL, set_buffer_to, (void *)&val[1]);
    //Sonda que comprueba que el Inv siempre se cumpla
    while (1){
        yield();
        pthread_mutex_lock(&mutex);     //Inicio SC
        //Inv: { \forall i: buffer[i]=buffer[0] }
        for(i=0; i<CAPACIDAD; i++){
            assert(buffer[i]==buffer[0]);
            yield();
        }
        pthread_mutex_unlock(&mutex);
    }
    //Aqui nunca llega
}

//Poner todo el buffer en un valor
void *set_buffer_to(void *arg){
    int val, i;

    val = *(int *)arg;

    while(1){
        yield();
        pthread_mutex_lock(&mutex);
        for (i = 0; i < CAPACIDAD; i++){
            buffer[i] = val;
            yield();
        }
        pthread_mutex_unlock(&mutex);
        yield();
    }
}

void yield(void){
    if(rand()%2){
        sched_yield();
    }
}