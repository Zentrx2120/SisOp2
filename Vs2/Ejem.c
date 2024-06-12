#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Estructura de un registro en el journal
struct JournalRecord {
    char operation[MAX_SIZE];
};

// Función para escribir en el archivo de registro (journal)
void write_to_journal(const char *operation) {
    struct JournalRecord record;
    strncpy(record.operation, operation, MAX_SIZE);

    FILE *journal_file = fopen("journal.txt", "a"); // Abrir el archivo de registro en modo de añadir
    if (journal_file == NULL) {
        printf("Error al abrir el archivo de registro.\n");
        return;
    }

    fwrite(&record, sizeof(struct JournalRecord), 1, journal_file); // Escribir el registro en el archivo de registro
    fclose(journal_file); // Cerrar el archivo de registro
}

// Función para simular una operación de escritura en disco
void write_to_disk(const char *data) {
    // Simular una operación de escritura en disco
    printf("Escribiendo en disco: %s\n", data);
}

// Función para escribir datos en un archivo, simulando una operación que podría fallar
void write_to_file(const char *data) {
    FILE *file = fopen("data.txt", "w");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    if (fprintf(file, "%s", data) < 0) { // Intenta escribir en el archivo
        printf("Error al escribir en el archivo.\n");
        fclose(file);
        return;
    }

    fclose(file);
}

// Función principal
int main() {
    const char *data_to_write = "Datos importantes";

    // Escribir en el archivo de registro antes de escribir en disco
    write_to_journal("Escritura en disco");

    // Realizar la operación de escritura en disco
    write_to_disk(data_to_write);

    // Escribir en el archivo con posibilidad de fallo
    write_to_file(data_to_write);

    return 0;
}