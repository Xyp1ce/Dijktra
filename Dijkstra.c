#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char[1] name;   // Estará marcado por una sola letra
    Path* paths[5]; // Lista de apuntadores
    int quant;      // Cantidad de caminos actuales
}Node;

typedef struct {
    Node dest;
    int weight;
}Path;

Node* searchLowestPathWeight(*Node node);
Node* createNode(char nm) // nm -> name
Path* addPath(int wgt, Node dst); // wgt -> weight | ogn -> origin | dst -> destination

int main() {
    // Creamos los nodos de nuestro grafo
    nodeA = createNode('A');
    nodeB = createNode('B');
    nodeC = createNode('C');
    nodeD = createNode('D');
    nodeE = createNode('E');
    nodeF = createNode('F');
    // Asignamos caminos a cada nodo
    // Nodo A
    nodeA.paths = addPath(10, NULL, nodeD);
    nodeA.paths = addPath(50, NULL, nodeB);
    nodeA.paths = addPath(45, NULL, nodeC);
    // Nodo B
    nodeB.paths = addPath(10, nodeB, nodeC);
    nodeB.paths = addPath(15, nodeB, nodeD);
    // Nodo C
    nodeC.paths = addPath(30, nodeC, nodeE);
    // Nodo D
    nodeD.paths = addPath(10, nodeD, nodeA);
    nodeD.paths = addPath(15, nodeD, nodeE);
    // Nodo E
    nodeE.paths = addPath();
    nodeE.paths = addPath();
    nodeE.paths = addPath();
    // Nodo F
    nodeE.paths = addPath();
    return 0;
}

Node* createNode(char nm) {
    // Reservamos memoria para un nuevo nodo
    newNode = (Node*)calloc(1, sizeof(Path));
    // Asignamos nombre
    newNode.name = nm;
    // Retornar una referencia al nuevo nodo
    return newNode;
}

Path* addPath(int wgt, Node dst) {
    // Reservamos memoria para un nuevo camino
    newPath = (Path*)calloc(1, sizeof(Path));
    // Crear copia de la cantidad de caminos 
     int index = ogn.quant;
    // Asignamos valores
    newPath.weight = wgt;
    newPath.dest = dst;
    // Poner camino en la lista
    ogn.paths[index] = newPath;
    // Incrementar la cantidad de caminos actuales
    ogn.quant++;
    // Retornamos referencia al nuevo camino
    return newPath;
}
