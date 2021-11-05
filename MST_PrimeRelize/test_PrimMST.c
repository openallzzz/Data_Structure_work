#define _CRT_SECURE_NO_WARNINGS 1

#include "Prim_MST_Statement.h"

int main() {
	MatrixGraph graph;
	InitGraph(&graph, 6);
	InsertVertex(&graph, 'a'); // 0
	InsertVertex(&graph, 'b'); // 1
	InsertVertex(&graph, 'c'); // 2
	InsertVertex(&graph, 'd'); // 3
	InsertVertex(&graph, 'e'); // 4
	InsertVertex(&graph, 'f'); // 5

	InsertEdge(&graph, 0, 5, 13);
	InsertEdge(&graph, 0, 1, 9);
	InsertEdge(&graph, 0, 2, 7);
	InsertEdge(&graph, 0, 3, 8);
	InsertEdge(&graph, 1, 5, 17);
	InsertEdge(&graph, 1, 4, 12);
	InsertEdge(&graph, 4, 5, 18);
	InsertEdge(&graph, 2, 4, 10);
	InsertEdge(&graph, 2, 3, 5);
	InsertEdge(&graph, 3, 4, 24);

	//ShowMatrix(&graph);
	MST_Prim(&graph, 'c');
	return 0;
}