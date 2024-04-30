#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 // Tamaño máximo del marco de página definido

// Estructura para representar una página
typedef struct {
    int pageNumber;
    int lastUsed;
} Page;

// Función para encontrar el índice de la página menos recientemente usada
int findLeastRecentlyUsed(Page pages[], int n) {
    int leastRecentlyUsedIndex = 0;
    int minLastUsed = pages[0].lastUsed;
    
    for (int i = 1; i < n; i++) {
        if (pages[i].lastUsed < minLastUsed) {
            minLastUsed = pages[i].lastUsed;
            leastRecentlyUsedIndex = i;
        }
    }
    
    return leastRecentlyUsedIndex;
}

// Función para imprimir el estado actual de los marcos de página
void printFrames(Page frames[], int n) {
    printf("Estado actual de los marcos de pagina: ");
    for (int i = 0; i < n; i++) {
        if (frames[i].pageNumber == -1) {
            printf("[ ] ");
        } else {
            printf("[%d] ", frames[i].pageNumber);
        }
    }
    printf("\n");
}

//-----------------------------------------------------------------------
int main() {
    int referenceString[] = {1, 2, 3, 4, 2, 1, 5, 2, 4, 5}; // Cadena de referencia
    int n = sizeof(referenceString) / sizeof(referenceString[0]);
    
    Page frames[MAX_FRAMES]; // Array para representar los marcos de página
    
    // Inicializar marcos de página
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i].pageNumber = -1; // -1 indica que el marco está vacío
        frames[i].lastUsed = 0;
    }
    
    // Simulación del acceso a las páginas y sustitución de páginas según el algoritmo LRU
    for (int i = 0; i < n; i++) {
        int currentPage = referenceString[i];
        int pageFound = 0;
        
        // Verificar si la página ya está en memoria
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j].pageNumber == currentPage) {
                frames[j].lastUsed = i + 1; // Actualizar el contador de último uso
                pageFound = 1;
                break;
            }
        }
        
        // Si la página no está en memoria, reemplazar la página LRU
        if (!pageFound) {
            int indexToReplace = findLeastRecentlyUsed(frames, MAX_FRAMES);
            frames[indexToReplace].pageNumber = currentPage;
            frames[indexToReplace].lastUsed = i + 1; // Actualizar el contador de último uso
        }
        
        // Imprimir el estado actual de los marcos de página después de cada acceso a la página
        printf("Acceso a pagina %d:\n", currentPage);
        printFrames(frames, MAX_FRAMES);
        printf("\n");
    }
    
    return 0;
}