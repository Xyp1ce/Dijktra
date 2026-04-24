#include <stdio.h>
#include <stdlib.h>

#define INF 9999999

typedef struct Nodo{
	char id;			 // Identificado por una letra (A, B, C, ..., Z)
	struct Nodo **salidas;  // Caminos que salen del nodo
	int *pesos;			 // Lista de pesos
	int cant;			// Cantidad de nodos conectados
} Nodo;

typedef struct
{
	int *distancias;	// arreglo de distancias
	int *anteriores;	// arreglo de nodo anteriores para reconstruccion de camino
	int numNodos;
} TablaResultados;

Nodo* crearNodo(char id); 
void agregarConexionUnidireccional(Nodo* nodoOriginal, Nodo* nodoSalida, int peso);
void conectarNodos(Nodo* nodoA, Nodo* nodoB, int peso);

TablaResultados *dijkstra(Nodo **nodos, int numNodos, int indiceInicio);

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

	conectarNodos(nodoA, nodoC, 45);
	printf("Conexion bidireccional entre A y C creada\n");

	conectarNodos(nodoA, nodoD, 10);
	printf("Conexion bidireccional entre A y D creada\n");

	// crear arreglo de nodos
	Nodo *nodos[] = {nodoA, nodoB, nodoC, nodoD};
	int numNodos = sizeof(nodos) / sizeof(nodos[0]);

	TablaResultados *resultado = dijkstra(nodos, numNodos, 0);

	printf("\n--- Resultados Dijkstra desde Nodo %c ---\n", nodos[0]->id);
	for(int i = 0; i < numNodos; i++) {
		printf("Distancia a %c: %d\n", nodos[i]->id, resultado->distancias[i]);
	}

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

TablaResultados *dijkstra(Nodo **nodos, int numNodos, int indiceInicio)
{
	// crear struct Resultado
	TablaResultados *resultado = (TablaResultados*) malloc(sizeof(TablaResultados));
	resultado->numNodos = numNodos;

	resultado->distancias = (int*) malloc(numNodos * sizeof(int));
	resultado->anteriores = (int*) malloc(numNodos * sizeof(int));

	// array tmp
	int *visitados = (int*) malloc(numNodos * sizeof(int));

	//paso 1. inicializar distancias, origen en 0, lo demas INF
	for (int i = 0; i < numNodos; i++)
	{
		resultado->distancias[i] = INF;
		resultado->anteriores[i] = -1;	// sin nodo anterior aun
		visitados[i] = 0;		// false
	}

	resultado->distancias[indiceInicio] = 0;

	//paso 2. encontrar el camino mas corto para todos los vertices
	for (int conteo = 0; conteo < numNodos - 1; conteo++)
	{
		int minDistancia = INF;
		int u = -1;	// idx del nodo con distancia minima
		for (int v = 0; v < numNodos; v++)
		{
			if (!visitados[v] && resultado->distancias[v] <= minDistancia)
			{
				minDistancia = resultado->distancias[v];
				u = v;
			}
		}
		// si todos son inalcanzables, salir del loop
		if (u == -1) break;

		// marcar el nodo elegido como visitado
		visitados[u] = 1;

		// actualizar distancia de los nodos adyacentes del nodo elegido
		Nodo *actual = nodos[u];
		for (int i = 0; i < actual->cant; i++)
		{
			Nodo *destino_adyacente = actual->salidas[i];
			int peso_adyacente = actual->pesos[i];

			// buscar idx del destino en array principal
			int idx_destino = -1;
			for (int j = 0; j < numNodos; j++)
			{
				if (nodos[j] == destino_adyacente)
				{
					idx_destino = j;
					break;
				}
			}
			//relajar arista
			if (idx_destino != -1 && !visitados[idx_destino] && resultado->distancias[u] != INF &&
				resultado->distancias[u] + peso_adyacente < resultado->distancias[idx_destino])
			{
				resultado->distancias[idx_destino] = resultado->distancias[u] + peso_adyacente;
				resultado->anteriores[idx_destino] = u;
			}
		}
	}
	free(visitados);

	return resultado;
}
