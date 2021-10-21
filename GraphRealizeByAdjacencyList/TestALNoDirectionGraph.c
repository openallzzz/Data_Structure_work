#define _CRT_SECURE_NO_WARNINGS 1

#include "GraphOperationsStatement.h"

int main() {
	ALGraph graph;
	BuildALGraph(&graph);
	showALGraph(&graph);
	return 0;
}