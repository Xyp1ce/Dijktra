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
	// crear arreglo de nodos
	Nodo *nodos[] = {nodoA, nodoB, nodoC, nodoD, nodoE, nodoF, nodoG, nodoH, nodoI, nodoJ, nodoK, nodoL, nodoM, nodoN, nodoO, nodoP, nodoQ, nodoR, nodoS, nodoT};
	int numNodos = sizeof(nodos) / sizeof(nodos[0]);

    int posNodo = 19;

	TablaResultados *resultado = dijkstra(nodos, numNodos, posNodo);

	printf("\n--- Resultados Dijkstra desde Nodo %c ---\n", nodos[posNodo]->id);
	for(int i = 0; i < numNodos; i++) {
		printf("Distancia a %c: %d\t anterior = %c\n", nodos[i]->id, resultado->distancias[i], resultado->anteriores[i] != -1 ? nodos[resultado->anteriores[i]]->id : '-');
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

	// array tmp para nodos visitado
	int *visitados = (int*) malloc(numNodos * sizeof(int));

	//paso 1. inicializar distancias, origen en 0, lo demas INF
	for (int i = 0; i < numNodos; i++)
	{
		resultado->distancias[i] = INF;	// todos inician en INFINITO
		resultado->anteriores[i] = -1;	// sin nodos anteriores aun
		visitados[i] = 0;				// por defaul, ninguna esta visitado
	}

	resultado->distancias[indiceInicio] = 0;

	//paso 2. encontrar el camino mas corto para todos los vertices
	for (int conteo = 0; conteo < numNodos - 1; conteo++)	// se cuentan todos los nodos menos 1, porque el ultimo se visitara automaticamente
	{
		int distMinActual = INF;	// inicializar distancia mas corta
		int nodoMin = -1;		// indice del nodo con la menor distancia (para seguir)

		// encontrar el nodo con la distancia mas corta que no ha sido visitado
		for (int v = 0; v < numNodos; v++)
		{
			// si el nodo no ha sido visitado y su distancia es menor a la distancia minima actual
			if (!visitados[v] && resultado->distancias[v] <= distMinActual)
			{
				distMinActual = resultado->distancias[v];	// actualizar distancia minima en la tabla
				nodoMin = v;	// seteamos el indice del nuevo nodo a visitar
			}
		}
		// si todos los nodos son inalcanzables, salir del loop
		if (nodoMin == -1) break;

		// marcar el nodo elegido como visitado para no volver a visitarlo
		visitados[nodoMin] = 1;

		// actualizar distancia de los nodos adyacentes del nodo elegido
		Nodo *actual = nodos[nodoMin];
		for (int i = 0; i < actual->cant; i++)
		{
			Nodo *adyacenteActual = actual->salidas[i];
			int pesoAdyacente = actual->pesos[i];

			// encontrar el primer nodo adyacente y encontrar su indice en el arreglo de nodos para actualizar su distancia
			int idxDestino = -1;
			for (int j = 0; j < numNodos; j++)
			{
				if (nodos[j] == adyacenteActual)
				{
					idxDestino = j;
					break;
				}
			}
			if (idxDestino != -1 &&	// si encontramos el indice del primer nodo adyacente
				!visitados[idxDestino] && // el nodo adyacente no ha sido visitado
				resultado->distancias[nodoMin] != INF &&	// el nodo actual es alcanzable
				resultado->distancias[nodoMin] + pesoAdyacente < resultado->distancias[idxDestino])	// la distancia al nodo destino a traves del nodo actual es menor que la distancia previamente registrada
			{
				resultado->distancias[idxDestino] = resultado->distancias[nodoMin] + pesoAdyacente;	// actualizar la distancia al nodo adyacente
				resultado->anteriores[idxDestino] = nodoMin;	// agregar al arreglo de anteriores el nodo actual para llegar al nodo adyacente
			}
		}
	}
	free(visitados);

	return resultado;
}
