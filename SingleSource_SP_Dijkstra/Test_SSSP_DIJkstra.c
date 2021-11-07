#define _CRT_SECURE_NO_WARNINGS 1

#include "SSSP_DIJ_Statement.h"

int main() {
	MatrixGraph graph;
	InitGraph(&graph, 7);
	InsertVertex(&graph, 1);
	InsertVertex(&graph, 2);
	InsertVertex(&graph, 3);
	InsertVertex(&graph, 4);
	InsertVertex(&graph, 5);
	InsertVertex(&graph, 6);
	InsertVertex(&graph, 7);

	InsertEdge(&graph, 0, 1, 13);
	InsertEdge(&graph, 0, 2, 8);
	InsertEdge(&graph, 0, 4, 30);
	InsertEdge(&graph, 0, 6, 32);
	InsertEdge(&graph, 1, 6, 7);
	InsertEdge(&graph, 1, 5, 9);
	InsertEdge(&graph, 2, 3, 5);
	InsertEdge(&graph, 3, 4, 6);
	InsertEdge(&graph, 4, 5, 2);
	InsertEdge(&graph, 5, 6, 17);

	SSSP_DIJ(&graph, 0);
	return 0;
}