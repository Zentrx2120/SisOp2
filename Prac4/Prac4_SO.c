#include <stdio.h>//Entrada y salida de datos
#include <stdlib.h>// Funciones utiles

#define MAX_PROCESOS 10 //Numero de procesos Maximo

// Estructura para representar un proceso
typedef struct {//Estructura de proceso
    int id;
    int tiempo_llegada;
    int tiempo_ejecucion;
    int prioridad;
} Proceso;

// Función para ejecutar un proceso
void ejecutarProceso(Proceso proceso) {
    printf("Ejecutando proceso %d con prioridad %d\n", proceso.id, proceso.prioridad);
}

int main() {
    Proceso procesos[MAX_PROCESOS];
    int n_procesos;
    
    // Obtener el número de procesos desde la entrada estándar
    printf("Ingrese el numero de procesos: ");
    scanf("%d", &n_procesos);
    
    // Leer información de cada proceso
    printf("Ingrese informacion de cada proceso (id, llegada, ejecucion, prioridad):\n");
    for (int i = 0; i < n_procesos; i++) {
        scanf("%d %d %d %d", &procesos[i].id, &procesos[i].tiempo_llegada, 
        &procesos[i].tiempo_ejecucion, &procesos[i].prioridad);
    }
    
    // Ordenar los procesos por tiempo de llegada
    for (int i = 0; i < n_procesos - 1; i++) {
        for (int j = 0; j < n_procesos - i - 1; j++) {
            if (procesos[j].tiempo_llegada > procesos[j+1].tiempo_llegada) {
                Proceso temp = procesos[j];
                procesos[j] = procesos[j+1];
                procesos[j+1] = temp;
            }
        }
    }
    
    // Simulación de planificación MQS
    int tiempo_actual = 0;
    for (int i = 0; i < n_procesos; i++) {
        while (tiempo_actual < procesos[i].tiempo_llegada) {
            tiempo_actual++;
        }
        ejecutarProceso(procesos[i]);
        tiempo_actual += procesos[i].tiempo_ejecucion;
    }
    
    printf("Todos los procesos han terminado.\n");
    
    return 0;
}