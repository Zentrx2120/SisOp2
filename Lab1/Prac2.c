#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la memoria física
#define MEMORIA_FISICA_SIZE 8
char *memoria_fisica[MEMORIA_FISICA_SIZE];
int marcos_ocupados[MEMORIA_FISICA_SIZE];

// Definición de la memoria virtual
#define MEMORIA_VIRTUAL_SIZE 16
#define PAGINA_SIZE 4
char *memoria_virtual[MEMORIA_VIRTUAL_SIZE];
int paginas_en_uso[MEMORIA_VIRTUAL_SIZE];

// Área de swapping
#define SWAPPING_SIZE 8
char *swapping_area[SWAPPING_SIZE];
int paginas_swapping[SWAPPING_SIZE];

// Función para asignar una página en memoria física
void asignar_pagina_memoria_fisica(int pagina, char *contenido) {
    if (pagina >= 0 && pagina < MEMORIA_FISICA_SIZE) {
        memoria_fisica[pagina] = contenido;
        marcos_ocupados[pagina] = 1;
        printf("Se asignó la página %d en memoria física con contenido: %s\n", pagina, contenido);
    } else {
        printf("Error: Página fuera de rango\n");
    }
}

// Función para obtener el contenido de una página en memoria física
char *obtener_contenido_memoria_fisica(int pagina) {
    if (pagina >= 0 && pagina < MEMORIA_FISICA_SIZE) {
        return memoria_fisica[pagina];
    } else {
        printf("Error: Página fuera de rango\n");
        return NULL;
    }
}

// Función para asignar una página en memoria virtual
void asignar_pagina_memoria_virtual(int pagina, char *contenido) {
    if (pagina >= 0 && pagina < MEMORIA_VIRTUAL_SIZE) {
        memoria_virtual[pagina] = contenido;
        paginas_en_uso[pagina] = 1;
        printf("Se asignó la página %d en memoria virtual con contenido: %s\n", pagina, contenido);
    } else {
        printf("Error: Página fuera de rango\n");
    }
}

// Función para obtener el contenido de una página en memoria virtual
char *obtener_contenido_memoria_virtual(int pagina) {
    if (pagina >= 0 && pagina < MEMORIA_VIRTUAL_SIZE) {
        return memoria_virtual[pagina];
    } else {
        printf("Error: Página fuera de rango\n");
        return NULL;
    }
}

// Función para realizar swapping de una página
void swap(int pagina_memoria_virtual, int pagina_swapping) {
    char *contenido = swapping_area[pagina_swapping];
    if (contenido != NULL) {
        printf("Se movió la página %d desde el área de swapping al marco de página %d\n", pagina_swapping, pagina_memoria_virtual);
        asignar_pagina_memoria_fisica(pagina_memoria_virtual, contenido);
        swapping_area[pagina_swapping] = NULL;
        paginas_swapping[pagina_swapping] = 0;
    } else {
        printf("Error: Página no encontrada en el área de swapping\n");
    }
}

// Algoritmo de reemplazo FIFO (First In First Out)
int fifo() {
    for (int i = 0; i < MEMORIA_FISICA_SIZE; ++i) {
        if (marcos_ocupados[i] == 0) {
            return i;
        }
    }
    return 0; // Si no hay marcos libres, se devuelve el primer marco
}

// Función principal
int main() {
    // Asignar páginas en memoria física
    asignar_pagina_memoria_fisica(0, "Contenido de la página 0");
    asignar_pagina_memoria_fisica(1, "Contenido de la página 1");

    // Asignar páginas en memoria virtual
    asignar_pagina_memoria_virtual(0, "Contenido de la página 0 en memoria virtual");
    asignar_pagina_memoria_virtual(1, "Contenido de la página 1 en memoria virtual");

    // Realizar swapping de una página (simulado)
    swapping_area[2] = "Contenido de la pagina 2 en swapping";
    paginas_swapping[2] = 1;
    int marco_libre = fifo(); // Se utiliza el algoritmo FIFO para encontrar un marco libre
    swap(marco_libre, 2);

    // Obtener contenido de una página en memoria física
    char *contenido_pagina = obtener_contenido_memoria_fisica(2);
    if (contenido_pagina != NULL) {
        printf("Contenido de la pagina 2 en memoria física: %s\n", contenido_pagina);
    }

    return 0;
}