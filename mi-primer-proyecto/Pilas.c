#include <stdio.h>
#include <stdlib.h>

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
    Nodo *tope;
} Pila;

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

void inicializarPila(Pila *pila) {
    pila->tope = NULL;
}

void insertarPila(Pila *pila, Libro libro) {
    Nodo *nuevo = malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("\nNo hay memoria disponible.\n");
        return;
    }

    nuevo->dato = libro;
    nuevo->siguiente = pila->tope;
    pila->tope = nuevo;
    printf("\nLibro agregado a la pila correctamente.\n");
}

void mostrarPila(Pila *pila) {
    Nodo *actual = pila->tope;

    if (actual == NULL) {
        printf("\nLa pila esta vacia.\n");
        return;
    }

    printf("\nLIBROS EN LA PILA:\n");
    while (actual != NULL) {
        mostrarLibro(actual->dato);
        actual = actual->siguiente;
    }
}

int buscarPorCodigoPila(Pila *pila, int codigo) {
    Nodo *actual = pila->tope;

    while (actual != NULL) {
        if (actual->dato.codigo == codigo) {
            mostrarLibro(actual->dato);
            return 1;
        }
        actual = actual->siguiente;
    }
    return 0;
}

int eliminarPorCodigoPila(Pila *pila, int codigo) {
    Nodo *actual = pila->tope;
    Nodo *anterior = NULL;

    while (actual != NULL && actual->dato.codigo != codigo) {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (actual == NULL) {
        return 0;
    }

    if (anterior == NULL) {
        pila->tope = actual->siguiente;
    } else {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    return 1;
}

void liberarPila(Pila *pila) {
    while (pila->tope != NULL) {
        Nodo *actual = pila->tope;
        pila->tope = actual->siguiente;
        free(actual);
    }
}

int main(void) {
    Pila pila;
    Libro libro;
    char opcion;

    inicializarPila(&pila);

    do {
        printf("\n===== MENU PILA (4.1) =====");
        printf("\na) Ingresar nuevos libros");
        printf("\nb) Ver todos los libros");
        printf("\nc) Bajas de libros");
        printf("\nd) Buscar un libro por codigo");
        printf("\ne) Salir");
        printf("\nSeleccione una opcion: ");
        scanf(" %c", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 'a':
            case 'A':
                leerLibro(&libro);
                insertarPila(&pila, libro);
                break;
            case 'b':
            case 'B':
                mostrarPila(&pila);
                break;
            case 'c':
            case 'C':
                printf("\nIngrese el codigo del libro a eliminar: ");
                scanf("%d", &libro.codigo);
                limpiarBuffer();
                if (eliminarPorCodigoPila(&pila, libro.codigo)) {
                    printf("\nLibro eliminado correctamente.\n");
                } else {
                    printf("\nNo se encontro el libro.\n");
                }
                break;
            case 'd':
            case 'D':
                printf("\nIngrese el codigo a buscar: ");
                scanf("%d", &libro.codigo);
                limpiarBuffer();
                if (!buscarPorCodigoPila(&pila, libro.codigo)) {
                    printf("\nNo se encontro el libro.\n");
                }
                break;
            case 'e':
            case 'E':
                printf("\nSaliendo del programa Pila...\n");
                break;
            default:
                printf("\nOpcion invalida.\n");
                break;
        }
    } while (opcion != 'e' && opcion != 'E');

    liberarPila(&pila);
    return 0;
}