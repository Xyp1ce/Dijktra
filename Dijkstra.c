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
