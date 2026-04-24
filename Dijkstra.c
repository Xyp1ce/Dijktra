#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
    char id;             // Identificado por una letra (A, B, C, ..., Z)
    struct Nodo **salidas;  // Caminos que salen del nodo
    int *pesos;             // Lista de pesos
    int cant;            // Cantidad de nodos conectados
} Nodo;

Nodo* crearNodo(char id); 
void agregarConexionUnidireccional(Nodo* nodoOriginal, Nodo* nodoSalida, int peso);
void conectarNodos(Nodo* nodoA, Nodo* nodoB, int peso);

int main() {
    Nodo *nodoA = crearNodo('A');
    printf("Nodo %c creado\n", nodoA->id);
    Nodo *nodoB = crearNodo('B');
    printf("Nodo %c creado\n", nodoB->id);
    Nodo *nodoC = crearNodo('C');
    printf("Nodo %c creado\n", nodoC->id);
    Nodo *nodoD = crearNodo('D');
    printf("Nodo %c creado\n", nodoD->id);

    printf("\n--- Creando conexiones no dirigidas ---\n");
    conectarNodos(nodoA, nodoB, 50);
    printf("Conexion bidireccional entre A y B creada\n");
    
    conectarNodos(nodoA, nodoC, 45);
    printf("Conexion bidireccional entre A y C creada\n");
    
    conectarNodos(nodoA, nodoD, 10);
    printf("Conexion bidireccional entre A y D creada\n");

    return 0;
}

Nodo* crearNodo(char id) {
    Nodo *nuevoNodo = (Nodo*) calloc(1, sizeof(Nodo));      
    nuevoNodo->id = id;                                     
    nuevoNodo->salidas = NULL;                              
    nuevoNodo->pesos = NULL;                                
    nuevoNodo->cant = 0;                                    

    return nuevoNodo;                                       
}

void agregarConexionUnidireccional(Nodo* nodoOriginal, Nodo* nodoSalida, int peso) {
    nodoOriginal->cant++;
    int indice = nodoOriginal->cant;                      
    
    Nodo **tempSalidas = (Nodo**) realloc(nodoOriginal->salidas, indice * sizeof(Nodo*));
    if(!tempSalidas) {
        printf("Error, Fallo al asignar memoria para las salidas. \n");
        exit(1);
    }
    nodoOriginal->salidas = tempSalidas;
    nodoOriginal->salidas[indice-1] = nodoSalida;

    int *tempPesos = (int*) realloc(nodoOriginal->pesos, indice * sizeof(int));
    if(!tempPesos) {
        printf("Error, Fallo al asignar memoria para los pesos. \n");
        exit(1);
    }
    nodoOriginal->pesos = tempPesos;
    nodoOriginal->pesos[indice-1] = peso;
}

// Nueva función para establecer la conexión bidireccional (Grafo no dirigido)
void conectarNodos(Nodo* nodo1, Nodo* nodo2, int peso) {
    // Se agrega la conexión en ambos sentidos
    agregarConexionUnidireccional(nodo1, nodo2, peso);
    agregarConexionUnidireccional(nodo2, nodo1, peso);
}
