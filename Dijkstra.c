#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    char id;             // Identificado por una letra (A, B, C, ..., Z)
    struct Nodo **salidas;  // Caminos que salen del nodo
    int *pesos;            // Lista de pesos
    int cant;           // Cantidad de nodos
} Nodo;

Nodo* crearNodo(char id); 
void agregarSalida(Nodo* nodoOriginal, Nodo* nodoSalida, int peso);

int main() {
    Nodo *nodoA = crearNodo('A');
    printf("Nodo %c creado\n", nodoA->id);
    Nodo *nodoB = crearNodo('B');
    printf("Nodo %c creado\n", nodoB->id);
    Nodo *nodoC = crearNodo('C');
    printf("Nodo %c creado\n", nodoC->id);
    Nodo *nodoD = crearNodo('D');
    printf("Nodo %c creado\n", nodoD->id);

    agregarSalida(nodoA, nodoB, 50);
    printf("Salida de nodo A a nodo B creada\n");
    agregarSalida(nodoA, nodoC, 45);
    printf("Salida de nodo A a nodo C creada\n");
    agregarSalida(nodoA, nodoD, 10);
    printf("Salida de nodo A a nodo D creada\n");
    return 0;
}

Nodo* crearNodo(char id) {
    Nodo *nuevoNodo = (Nodo*) calloc(1, sizeof(Nodo));      // Asignacion de memoria para nuevo nodo
    nuevoNodo->id = id;                                     // Asiganar identificador al nodo
    nuevoNodo->salidas = NULL;                              // Creacion de arreglo tamaño 0 de manera predeterminada
    nuevoNodo->pesos = NULL;                                // Creacion de arreglo tamaño 0 de manera predeterminada
    nuevoNodo->cant = 0;                                    // Inicializar contador de nodos salientes

    return nuevoNodo;                                       // Retornar direccion del nuevo nodo
}

void agregarSalida(Nodo* nodoOriginal, Nodo* nodoSalida, int peso) {
    nodoOriginal->cant++;
    int indice = nodoOriginal->cant;                      // Incrementar la cantidad de nodos que hay de salida
    
    Nodo **tempSalidas = (Nodo**) realloc(nodoOriginal->salidas, indice * sizeof(Nodo*));
    if(!tempSalidas) {
        printf("Error, Fallo al asignar memoria para las salidas. \n");
        exit(1);
    }
    nodoOriginal->salidas = tempSalidas;
    nodoOriginal->salidas[indice-1] = nodoSalida;

    int *tempPesos = (int*) realloc(nodoOriginal->pesos, indice * sizeof(int));
    if(!tempPesos) {
        printf("Error, Fallo al asignar memoria para las salidas. \n");
        exit(1);
    }
    nodoOriginal->pesos = tempPesos;
    nodoOriginal->pesos[indice-1] = peso;
}

