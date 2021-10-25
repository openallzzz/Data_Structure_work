#define _CRT_SECURE_NO_WARNINGS 1

#include "ConnectedGraphBFS_ALStatement.h"


int main() {
	ALGraph graph;
	InitALGraph(&graph);

	InsertVertex(&graph, 1);
	InsertVertex(&graph, 2);
	InsertVertex(&graph, 3);
	InsertVertex(&graph, 4);
	InsertVertex(&graph, 5);
	InsertVertex(&graph, 6);
	InsertVertex(&graph, 7);

	InsertEdge(&graph, 1, 3);
	InsertEdge(&graph, 1, 2);
	InsertEdge(&graph, 3, 2);
	InsertEdge(&graph, 2, 5);
	InsertEdge(&graph, 2, 4);
	InsertEdge(&graph, 5, 7);
	InsertEdge(&graph, 5, 6);
	showALGraph(&graph);
	
	GraphBFS_AL(&graph, 0);
	GraphBFS_AL(&graph, 1);
	GraphBFS_AL(&graph, 5);
	GraphBFS_AL(&graph, 3);
	GraphBFS_AL(&graph, 2);

	return 0;
}