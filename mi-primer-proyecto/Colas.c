#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nombre[40];
    char autor[40];
    char editorial[40];
    char pais[30];
    int anio;
    int edicion;
    char isbn[20];
} Libro;

typedef struct Nodo {
    Libro dato;
    struct Nodo *siguiente;
} Nodo;

typedef struct {
    Nodo *frente;
    Nodo *final;
} Cola;

void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void mostrarLibro(Libro libro) {
    printf("\nCodigo: %d", libro.codigo);
    printf("\nNombre: %s", libro.nombre);
    printf("\nAutor: %s", libro.autor);
    printf("\nEditorial: %s", libro.editorial);
    printf("\nPais: %s", libro.pais);
    printf("\nAnio: %d", libro.anio);
    printf("\nEdicion: %d", libro.edicion);
    printf("\nISBN: %s", libro.isbn);
    printf("\n--------------------------------------\n");
}

void leerLibro(Libro *libro) {
    printf("\nIngrese codigo: ");
    scanf("%d", &libro->codigo);
    limpiarBuffer();

    printf("Ingrese nombre: ");
    scanf("%39[^\n]", libro->nombre);
    limpiarBuffer();

    printf("Ingrese autor: ");
    scanf("%39[^\n]", libro->autor);
    limpiarBuffer();

    printf("Ingrese editorial: ");
    scanf("%39[^\n]", libro->editorial);
    limpiarBuffer();

    printf("Ingrese pais: ");
    scanf("%29[^\n]", libro->pais);
    limpiarBuffer();

    printf("Ingrese anio: ");
    scanf("%d", &libro->anio);
    limpiarBuffer();

    printf("Ingrese edicion: ");
    scanf("%d", &libro->edicion);
    limpiarBuffer();

    printf("Ingrese ISBN: ");
    scanf("%19[^\n]", libro->isbn);
    limpiarBuffer();
}

void inicializarCola(Cola *cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

void encolar(Cola *cola, Libro libro) {
    Nodo *nuevo = malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("\nNo hay memoria disponible.\n");
        return;
    }

    nuevo->dato = libro;
    nuevo->siguiente = NULL;

    if (cola->frente == NULL) {
        cola->frente = nuevo;
        cola->final = nuevo;
    } else {
        cola->final->siguiente = nuevo;
        cola->final = nuevo;
    }

    printf("\nLibro agregado a la cola correctamente.\n");
}

void mostrarCola(Cola *cola) {
    Nodo *actual = cola->frente;

    if (actual == NULL) {
        printf("\nLa cola esta vacia.\n");
        return;
    }

    printf("\nLIBROS EN LA COLA:\n");
    while (actual != NULL) {
        mostrarLibro(actual->dato);
        actual = actual->siguiente;
    }
}

int buscarPorNombreCola(Cola *cola, const char nombre[]) {
    Nodo *actual = cola->frente;

    while (actual != NULL) {
        if (strcmp(actual->dato.nombre, nombre) == 0) {
            mostrarLibro(actual->dato);
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}

int desencolar(Cola *cola, Libro *libro) {
    if (cola->frente == NULL) {
        return 0;
    }

    Nodo *actual = cola->frente;
    *libro = actual->dato;
    cola->frente = actual->siguiente;

    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(actual);
    return 1;
}

void liberarCola(Cola *cola) {
    Libro libro;
    while (desencolar(cola, &libro)) {
    }
}

int main(void) {
    Cola cola;
    Libro libro;
    char opcion;
    char nombre[40];

    inicializarCola(&cola);

    do {
        printf("\n===== MENU COLA (4.2) =====");
        printf("\na) Ingresar nuevos libros");
        printf("\nb) Ver todos los libros");
        printf("\nc) Bajas de libros");
        printf("\nd) Buscar un libro por nombre del libro");
        printf("\ne) Salir");
        printf("\nSeleccione una opcion: ");
        scanf(" %c", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 'a':
            case 'A':
                leerLibro(&libro);
                encolar(&cola, libro);
                break;
            case 'b':
            case 'B':
                mostrarCola(&cola);
                break;
            case 'c':
            case 'C':
                if (desencolar(&cola, &libro)) {
                    printf("\nLibro dado de baja (eliminado del frente):\n");
                    mostrarLibro(libro);
                } else {
                    printf("\nLa cola esta vacia. No hay libros para dar de baja.\n");
                }
                break;
            case 'd':
            case 'D':
                printf("\nIngrese el nombre del libro a buscar: ");
                scanf("%39[^\n]", nombre);
                limpiarBuffer();
                if (!buscarPorNombreCola(&cola, nombre)) {
                    printf("\nNo se encontro ese libro.\n");
                }
                break;
            case 'e':
            case 'E':
                printf("\nSaliendo del programa Cola...\n");
                break;
            default:
                printf("\nOpcion invalida.\n");
                break;
        }
    } while (opcion != 'e' && opcion != 'E');

    liberarCola(&cola);
    return 0;
}