#define _CRT_SECURE_NO_WARNINGS 1

#include "Topo_sortingStatement.h"

int main() {
	ALGraph graph;
	BuildALGraph(&graph);
	insertVertex(&graph, "C1");
	insertVertex(&graph, "C2");
	insertVertex(&graph, "C3");
	insertVertex(&graph, "C4");
	insertVertex(&graph, "C5");
	insertVertex(&graph, "C6");
	insertVertex(&graph, "C7");
	insertVertex(&graph, "C8");
	insertVertex(&graph, "C9");
	insertVertex(&graph, "C10");
	insertVertex(&graph, "C11");
	insertVertex(&graph, "C12");

	insertEdge(&graph, "C1", "C4", 1);
	insertEdge(&graph, "C1", "C2", 1);
	insertEdge(&graph, "C1", "C3", 1);
	insertEdge(&graph, "C1", "C12", 1);
	insertEdge(&graph, "C2", "C3", 1);
	insertEdge(&graph, "C3", "C5", 1);
	insertEdge(&graph, "C3", "C7", 1);
	insertEdge(&graph, "C3", "C8", 1);
	insertEdge(&graph, "C4", "C5", 1);
	insertEdge(&graph, "C5", "C7", 1);
	insertEdge(&graph, "C9", "C12", 1);
	insertEdge(&graph, "C9", "C10", 1);
	insertEdge(&graph, "C9", "C11", 1);
	insertEdge(&graph, "C10", "C12", 1);
	insertEdge(&graph, "C11", "C6", 1);
	insertEdge(&graph, "C6", "C8", 1);
	showALGraph(&graph);

	Topo_sort(&graph);

	return 0;
}