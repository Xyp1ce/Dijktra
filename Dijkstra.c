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
    printf("--- Creando nodos ---\n");
    Nodo *nodoA = crearNodo('A');
    Nodo *nodoB = crearNodo('B');
    Nodo *nodoC = crearNodo('C');
    Nodo *nodoD = crearNodo('D');
    Nodo *nodoE = crearNodo('E');
    Nodo *nodoF = crearNodo('F');
    Nodo *nodoG = crearNodo('G');
    Nodo *nodoH = crearNodo('H');
    Nodo *nodoI = crearNodo('I');
    Nodo *nodoJ = crearNodo('J');
    Nodo *nodoK = crearNodo('K');
    Nodo *nodoL = crearNodo('L');
    Nodo *nodoM = crearNodo('M');
    Nodo *nodoN = crearNodo('N');
    Nodo *nodoO = crearNodo('O');
    Nodo *nodoP = crearNodo('P');
    Nodo *nodoQ = crearNodo('Q');
    Nodo *nodoR = crearNodo('R');
    Nodo *nodoS = crearNodo('S');
    Nodo *nodoT = crearNodo('T');
    printf("\n--- Nodos creados ---\n");

    printf("\n--- Creando conexiones no dirigidas ---\n");
    conectarNodos(nodoA, nodoB, 100);
    conectarNodos(nodoA, nodoD, 30);
    conectarNodos(nodoA, nodoD, 85);

    conectarNodos(nodoB, nodoC, 100);
    conectarNodos(nodoB, nodoE, 40);
    conectarNodos(nodoB, nodoG, 70);
    conectarNodos(nodoB, nodoF, 45);

    conectarNodos(nodoC, nodoH, 60);
    conectarNodos(nodoC, nodoG, 55);

    conectarNodos(nodoD, nodoP, 50);

    conectarNodos(nodoE, nodoI, 10);

    conectarNodos(nodoF, nodoJ, 55);

    conectarNodos(nodoG, nodoL, 20);
    conectarNodos(nodoG, nodoK, 15);

    conectarNodos(nodoH, nodoL, 40);
    conectarNodos(nodoH, nodoN, 85);
    conectarNodos(nodoH, nodoO, 70);

    conectarNodos(nodoI, nodoP, 90);
    conectarNodos(nodoI, nodoJ, 60);

    conectarNodos(nodoJ, nodoK, 80);
    conectarNodos(nodoJ, nodoQ, 45);

    conectarNodos(nodoK, nodoM, 60);

    conectarNodos(nodoL, nodoM, 50);

    conectarNodos(nodoM, nodoS, 2);

    conectarNodos(nodoN, nodoO, 120);
    conectarNodos(nodoN, nodoO, 105);
    conectarNodos(nodoN, nodoT, 60);
    conectarNodos(nodoN, nodoS, 55);

    conectarNodos(nodoO, nodoT, 195);

    conectarNodos(nodoP, nodoR, 205);

    conectarNodos(nodoQ, nodoR, 5);

    conectarNodos(nodoR, nodoT, 230);

    conectarNodos(nodoS, nodoT, 25); 
    printf("\n--- Conexiones no dirigidas creadas ---\n");

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
