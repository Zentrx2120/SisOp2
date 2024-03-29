#include <stdio.h> //Entrada y salida 
#include <stdlib.h> // Funcionalidades
#include <unistd.h> //fork
#include <sys/wait.h> //Exclusiva de Linux para wait()

//El error q logre encontrar fueron las librerias 
int main (){
    int pid, status;

    switch (pid=fork()){
    case -1:
        /*Gestor de error*/
        exit (1);
        break;
    
    case 0:
        /*Proceso hijo*/
        printf("\n Proceso hijo. PID= %d\n", pid);
        break;

    default:
        /*Proceso Padre*/
        printf("\n Proceso padre. PID= %d\n", pid);
        /*Espera al final del proceso hijo*/
        wait(&status);
        break;
    }
    printf("\n Fin de la ejecucion\n");
    return 0;
}