#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 100
#define MAX_CONTENIDO 1000
#define MAX_JOURNAL 100

//---------------------------------------------------------------
//Estructuras de archivos, directorios y registros
typedef struct {
    char nombre[MAX_NOMBRE];
    char contenido[MAX_CONTENIDO];
} Archivo;

typedef struct {
    char nombre[MAX_NOMBRE];    //Nombre del directorio
    Archivo *archivos;          //Los archivos dentro del directorio
    int num_archivos;           //numero de los archivos dentro del directorio
} Directorio;

typedef struct {
    int numero_operacion;                       // Número de operación en el journal
    char operacion[MAX_NOMBRE];                 // Operación realizada: crear, eliminar, modificar
    char nombre_archivo[MAX_NOMBRE];            //Nombre del archivo
    char contenido_anterior[MAX_CONTENIDO];     //Contenido anterior
} Registro;
//----------------------------------------------------------------

// Funciones para operar en el sistema de archivos
void crearArchivo(Archivo *archivo, const char *nombre, const char *contenido) {
    strcpy(archivo->nombre, nombre);
    strcpy(archivo->contenido, contenido);
}

void eliminarArchivo(Archivo *archivo) {
    archivo->nombre[0] = '\0';
    archivo->contenido[0] = '\0';
}

void modificarArchivo(Archivo *archivo, const char *contenido) {
    strcpy(archivo->contenido, contenido);
}

void agregarRegistro(Registro *journal, int numero_operacion, const char *operacion, const char *nombre_archivo, const char *contenido_anterior) {
    journal->numero_operacion = numero_operacion;
    strcpy(journal->operacion, operacion);
    strcpy(journal->nombre_archivo, nombre_archivo);
    strcpy(journal->contenido_anterior, contenido_anterior);
}

// Función para imprimir el journal
void imprimirJournal(Registro *journals, int num_registros) {
    printf("Journal de cambios:\n");
    printf("Numero de operacion\tOperacion\tNombre de archivo\tContenido anterior\n");
    for (int i = 0; i < num_registros; i++) {
        printf("(%d)\t\t\t%s\t\t%s\t\t%s\n", journals[i].numero_operacion, journals[i].operacion, journals[i].nombre_archivo, journals[i].contenido_anterior);
    }
}

// Función principal
int main() {
    // Crear directorio raíz
    Directorio raiz;
    strcpy(raiz.nombre, "Raiz");
    raiz.num_archivos = 0;
    raiz.archivos = NULL;

    // Crear arreglo de registros (journal)
    Registro journals[MAX_JOURNAL];
    int num_registros = 0;

    // Ejemplo de uso: crear un archivo
    Archivo archivo1;
    crearArchivo(&archivo1, "archivo1.txt", "Contenido del archivo 1");
    raiz.archivos = &archivo1;
    raiz.num_archivos++;
    
    // Agregar registro al journal
    agregarRegistro(&journals[num_registros++], num_registros, "crear", "archivo1.txt", "");

    // Imprimir journal después de la primera operación
    imprimirJournal(journals, num_registros);

    // Ejemplo de uso: crear un segundo archivo
    Archivo archivo2;
    crearArchivo(&archivo2, "archivo2.txt", "Contenido del archivo 2");
    raiz.archivos = &archivo2;
    raiz.num_archivos++;

    // Agregar registro al journal
    agregarRegistro(&journals[num_registros++], num_registros, "crear", "archivo2.txt", "");

    // Imprimir journal después de la segunda operación
    imprimirJournal(journals, num_registros);

    // Ejemplo de uso: eliminar el segundo archivo
    eliminarArchivo(&archivo2);
    raiz.num_archivos--;

    // Agregar registro al journal
    agregarRegistro(&journals[num_registros++], num_registros, "eliminar", "archivo2.txt", "");

    // Imprimir journal después de la tercera operación
    imprimirJournal(journals, num_registros);

    // Ejemplo de uso: crear un tercer archivo y modificarlo dos veces
    Archivo archivo3;
    crearArchivo(&archivo3, "archivo3.txt", "Contenido del archivo 3");
    raiz.archivos = &archivo3;
    raiz.num_archivos++;

    // Agregar registro al journal
    agregarRegistro(&journals[num_registros++], num_registros, "crear", "archivo3.txt", "");

    // Imprimir journal después de la cuarta operación
    imprimirJournal(journals, num_registros);

    // Modificar el tercer archivo por primera vez
    modificarArchivo(&archivo3, "Nuevo contenido del archivo 3");

    // Agregar registro al journal
    agregarRegistro(&journals[num_registros++], num_registros, "modificar", "archivo3.txt", "Contenido del archivo 3");

    // Imprimir journal después de la quinta operación
    imprimirJournal(journals, num_registros);

    // Modificar el tercer archivo por segunda vez
    modificarArchivo(&archivo3, "Contenido modificado del archivo 3");

    // Agregar registro al journal
    agregarRegistro(&journals[num_registros++], num_registros, "modificar", "archivo3.txt", "Nuevo contenido del archivo 3");

    // Imprimir journal después de la sexta operación
    imprimirJournal(journals, num_registros);

    return 0;
}