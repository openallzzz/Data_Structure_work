#define _CRT_SECURE_NO_WARNINGS 1

#include "CriticalPath_Statement.h"

int main() {
	ALGraph graph;
	BuildALGraph(&graph);

	insertVertex(&graph, "V0");
	insertVertex(&graph, "V1");
	insertVertex(&graph, "V2");
	insertVertex(&graph, "V3");
	insertVertex(&graph, "V4");
	insertVertex(&graph, "V5");
	insertVertex(&graph, "V6");
	insertVertex(&graph, "V7");
	insertVertex(&graph, "V8");

	insertEdge(&graph, "V0", "V1", 6, "a1");
	insertEdge(&graph, "V0", "V2", 4, "a2");
	insertEdge(&graph, "V0", "V3", 5, "a3");
	insertEdge(&graph, "V1", "V4", 1, "a4");
	insertEdge(&graph, "V2", "V4", 1, "a5");
	insertEdge(&graph, "V3", "V5", 2, "a6");
	insertEdge(&graph, "V4", "V6", 9, "a7");
	insertEdge(&graph, "V4", "V7", 7, "a8");
	insertEdge(&graph, "V5", "V7", 4, "a9");
	insertEdge(&graph, "V6", "V8", 2, "a10");
	insertEdge(&graph, "V7", "V8", 4, "a11");

	showALGraph(&graph);
	CriticalPath(&graph);
	return 0;
}