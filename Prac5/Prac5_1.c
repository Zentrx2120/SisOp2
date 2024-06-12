/*  Absalon Cortes Sebastian
    Izoteco Zacarias Pedro Uriel
    11 de junio 2024
    version 1.00
    Practica 5 Evaluacion: Vectores txt
*/
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <windows.h>

// Función para calcular el módulo de un vector
double calcularModulo(int *vector, int tam) {
    double suma = 0.0;
    for (int i = 0; i < tam; i++) {
        suma += vector[i] * vector[i];
    }
    return sqrt(suma);
}

void wait(int seconds) {
    Sleep(seconds * 1000); // Sleep en Windows recibe milisegundos
}
//----------------------------------------------------------
int main() {
    FILE *file;
    int A[3] = {2, 3, 4};
    int B[3] = {5, 6, 7};
    int C[3];
    int D[3] = {1, 1, 1};
    int resultado[3];

    // Sumar los vectores A y B, guardar el resultado en C
    for (int i = 0; i < 3; i++) {
        C[i] = A[i] + B[i];
    }

    // Crear y escribir en vector.txt
    file = fopen("vector.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo vector.txt\n");
        return 1;
    }
    fprintf(file, "%d %d %d\n", C[0], C[1], C[2]);
    fclose(file);

    // Leer de vector.txt y restar el vector D
    file = fopen("vector.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo vector.txt\n");
        return 1;
    }
    fscanf(file, "%d %d %d", &C[0], &C[1], &C[2]);
    fclose(file);

    for (int i = 0; i < 3; i++) {
        resultado[i] = C[i] - D[i];
    }

    // Guardar el resultado en vector2.txt
    file = fopen("vector2.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo vector2.txt\n");
        return 1;
    }
    fprintf(file, "%d %d %d\n", resultado[0], resultado[1], resultado[2]);
    fclose(file);

    // Leer de vector2.txt y calcular el módulo del vector
    file = fopen("vector2.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo vector2.txt\n");
        return 1;
    }
    fscanf(file, "%d %d %d", &resultado[0], &resultado[1], &resultado[2]);
    fclose(file);

    double modulo = calcularModulo(resultado, 3);

    // Guardar el módulo en vector3.txt
    file = fopen("vector3.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo vector3.txt\n");
        return 1;
    }
    fprintf(file, "Modulo: %.2f\n", modulo);
    fclose(file);

    wait(10);

    // Eliminar vector3.txt
    if (remove("vector3.txt") != 0) {
        printf("Error al eliminar el archivo vector3.txt\n");
        return 1;
    }

    return 0;
}