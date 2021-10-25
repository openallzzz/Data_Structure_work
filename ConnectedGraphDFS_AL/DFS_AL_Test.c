#define _CRT_SECURE_NO_WARNINGS 1

#include "DFS_AL_Statement.h"

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

	printf("无向连通图的优先深度遍历结果：\n");
	DFS_AL(&graph, 0);
	return 0;
}