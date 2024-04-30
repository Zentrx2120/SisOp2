#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de la memoria física
#define MEMORIA_FISICA_SIZE 8
char *memoria_fisica[MEMORIA_FISICA_SIZE];

// Definición de la memoria virtual
#define MEMORIA_VIRTUAL_SIZE 16
#define PAGINA_SIZE 4
char *memoria_virtual[MEMORIA_VIRTUAL_SIZE];

// Área de swapping
#define SWAPPING_SIZE 8
char *swapping_area[SWAPPING_SIZE];

// Función para asignar una página en memoria física
void asignar_pagina_memoria_fisica(int pagina, char *contenido) {
    if (pagina >= 0 && pagina < MEMORIA_FISICA_SIZE) {
        memoria_fisica[pagina] = contenido;
        printf("Se asigno la pagina %d en memoria fisica con contenido: %s\n", pagina, contenido);
    } else {
        printf("Error: Pagina fuera de rango\n");
    }
}

// Función para obtener el contenido de una página en memoria física
char *obtener_contenido_memoria_fisica(int pagina) {
    if (pagina >= 0 && pagina < MEMORIA_FISICA_SIZE) {
        return memoria_fisica[pagina];
    } else {
        printf("Error: Pagina fuera de rango\n");
        return NULL;
    }
}

// Función para asignar una página en memoria virtual
void asignar_pagina_memoria_virtual(int pagina, char *contenido) {
    if (pagina >= 0 && pagina < MEMORIA_VIRTUAL_SIZE) {
        memoria_virtual[pagina] = contenido;
        printf("Se asigno la pagina %d en memoria virtual con contenido: %s\n", pagina, contenido);
    } else {
        printf("Error: Pagina fuera de rango\n");
    }
}

// Función para obtener el contenido de una página en memoria virtual
char *obtener_contenido_memoria_virtual(int pagina) {
    if (pagina >= 0 && pagina < MEMORIA_VIRTUAL_SIZE) {
        return memoria_virtual[pagina];
    } else {
        printf("Error: Pagina fuera de rango\n");
        return NULL;
    }
}

// Función para realizar swapping de una página
void swap(int pagina_memoria_virtual, int pagina_swapping) {
    char *contenido = swapping_area[pagina_swapping];
    if (contenido != NULL) {
        printf("Se movio la pagina %d desde el area de swapping al marco de pagina %d\n", pagina_swapping, pagina_memoria_virtual);
        asignar_pagina_memoria_fisica(pagina_memoria_virtual, contenido);
        swapping_area[pagina_swapping] = NULL;
    } else {
        printf("Error: Pagina no encontrada en el area de swapping\n");
    }
}

// Función principal
int main() {
    // Asignar páginas en memoria física
    asignar_pagina_memoria_fisica(0, "Contenido de la pagina 0");
    asignar_pagina_memoria_fisica(1, "Contenido de la pagina 1");

    // Asignar páginas en memoria virtual
    asignar_pagina_memoria_virtual(0, "Contenido de la pagina 0 en memoria virtual");
    asignar_pagina_memoria_virtual(1, "Contenido de la pagina 1 en memoria virtual");

    // Realizar swapping de una página
    swapping_area[2] = "Contenido de la pagina 2 en swapping";
    swap(2, 2);

    // Obtener contenido de una página en memoria física
    char *contenido_pagina = obtener_contenido_memoria_fisica(2);
    if (contenido_pagina != NULL) {
        printf("Contenido de la pagina 2 en memoria fisica: %s\n", contenido_pagina);
    }

    return 0;
}