#define _CRT_SECURE_NO_WARNINGS 1

#include "GraphOperationsStatement.h"

// 采用邻接表法构建无向图
void BuildALGraph(ALGraph* graph) {
	graph->setsOfVertex = (VertexNode*)malloc(sizeof(VertexNode) * MAX_VERTEXNUMS);

	int vertexNums = 0;
	int edgeNums = 0;
	printf("分别输入顶点和边的个数(num1 num2):\n");
	scanf("%d %d", &vertexNums, &edgeNums);
	getchar();

	graph->vertexNums = vertexNums;
	graph->edgeNums = edgeNums;

	// 输入图中各个顶点的信息
	for (int i = 0; i < graph->vertexNums; i++) {
		printf("输入第%d个顶点的信息：\n", i + 1);
		scanf("%c", &(graph->setsOfVertex[i].val));
		getchar();
		graph->setsOfVertex[i].p_firstAdjEdge = NULL;
	}

	// 输入各个边，构建邻接表
	VertexDataType v1 = 0;
	VertexDataType v2 = 0;
	int v1Index = 0;
	int v2Index = 0;
	for (int i = 0; i < graph->edgeNums; i++) {
		printf("输入第%d条边所依附的两个结点：\n", i + 1);
		scanf("%c", &v1);
		getchar();
		scanf("%c", &v2);
		getchar();

		v1Index = SearchVertexRetIndex(graph, v1);
		v2Index = SearchVertexRetIndex(graph, v2);

		EdgeNode* newEdgeNode0 = (EdgeNode*)malloc(sizeof(EdgeNode));
		newEdgeNode0->adjVertexIndex = v2Index;
		newEdgeNode0->p_nextEdge = graph->setsOfVertex[v1Index].p_firstAdjEdge;
		graph->setsOfVertex[v1Index].p_firstAdjEdge = newEdgeNode0;

		EdgeNode* newEdgeNode1 = (EdgeNode*)malloc(sizeof(EdgeNode));
		newEdgeNode1->adjVertexIndex = v1Index;
		newEdgeNode1->p_nextEdge = graph->setsOfVertex[v2Index].p_firstAdjEdge;
		graph->setsOfVertex[v2Index].p_firstAdjEdge = newEdgeNode1;
	}
}

// 在图中寻找值为val的顶点的索引
int SearchVertexRetIndex(ALGraph* graph, VertexDataType val) {

	for (int i = 0; i < graph->vertexNums; i++) {
		if (graph->setsOfVertex[i].val == val) {
			return i;
		}
	}

	return -1;
}

// 显示邻接表中的信息
void showALGraph(ALGraph* graph) {
	EdgeNode* cur = NULL;
	printf("\n");
	for (int i = 0; i < graph->vertexNums; i++) {
		printf("%c->", graph->setsOfVertex[i].val);
		cur = graph->setsOfVertex[i].p_firstAdjEdge;
		while (cur != NULL) {
			printf("%d->", cur->adjVertexIndex);
			cur = cur->p_nextEdge;
		}
		printf("NULL\n");
	}
}