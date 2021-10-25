#define _CRT_SECURE_NO_WARNINGS 1

#include "ConnectedGraphBFS_ALStatement.h"

// 初始化无向图
void InitALGraph(ALGraph* graph) {
	graph->setsOfVertex = (VertexNode*)malloc(sizeof(VertexNode) * MAX_VERTEXNUMS);
	graph->edgeNums = 0;
	graph->vertexNums = 0;

	graph->visited = (int*)malloc(sizeof(int) * MAX_VERTEXNUMS);
}

// 插入值为val的顶点
void InsertVertex(ALGraph* graph, VertexDataType val) {
	graph->setsOfVertex[graph->vertexNums].val = val;
	graph->setsOfVertex[graph->vertexNums].p_firstAdjEdge = NULL;
	graph->visited[graph->vertexNums] = 0;// 初始化插入时的结点未被访问
	graph->vertexNums++;

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

// 插入依附顶点val1和val2的边
void InsertEdge(ALGraph* graph, VertexDataType val_1, VertexDataType val_2) {
	int v1Index = 0;
	int v2Index = 0;

	v1Index = SearchVertexRetIndex(graph, val_1);
	v2Index = SearchVertexRetIndex(graph, val_2);


	// 无向图需要关联到一条边所依附的两个顶点，即联系X->Y的同时，也需要联系Y->X

	// 头插结点来构建每个顶点的邻接关系

	// X->Y
	EdgeNode* newEdgeNode0 = (EdgeNode*)malloc(sizeof(EdgeNode));
	if (newEdgeNode0 == NULL) {
		exit(0);
	}
	newEdgeNode0->adjVertexIndex = v2Index;
	newEdgeNode0->p_nextEdge = graph->setsOfVertex[v1Index].p_firstAdjEdge;
	graph->setsOfVertex[v1Index].p_firstAdjEdge = newEdgeNode0;

	// Y->X
	EdgeNode* newEdgeNode1 = (EdgeNode*)malloc(sizeof(EdgeNode));
	if (newEdgeNode1 == NULL) {
		exit(0);
	}
	newEdgeNode1->adjVertexIndex = v1Index;
	newEdgeNode1->p_nextEdge = graph->setsOfVertex[v2Index].p_firstAdjEdge;
	graph->setsOfVertex[v2Index].p_firstAdjEdge = newEdgeNode1;

	graph->edgeNums++;
}

// 显示邻接表中的信息
void showALGraph(ALGraph* graph) {
	EdgeNode* cur = NULL;
	printf("当前图的邻接表的状态：\n");
	for (int i = 0; i < graph->vertexNums; i++) {
		printf("Adjacency List[%d]: %d => ", i, graph->setsOfVertex[i].val);
		cur = graph->setsOfVertex[i].p_firstAdjEdge;
		while (cur != NULL) {
			printf("%d->", graph->setsOfVertex[cur->adjVertexIndex].val);
			cur = cur->p_nextEdge;
		}
		printf("NULL\n");
	}
}

// 广度优先遍历无向连通图
void GraphBFS_AL(ALGraph* graph, int startVertexIndex) {
	// 每一次调用广度优先遍历算法都要重置之前调用时被“充满”的已被访问过的标志
	memset(graph->visited, 0, MAX_VERTEXNUMS);
	printf("\n从值为%d的顶点开始广度优先遍历得结果为：", graph->setsOfVertex[startVertexIndex].val);
	LQueue queue;
	InitLQueue(&queue);
	push(&queue, &(graph->setsOfVertex[startVertexIndex].val)); // 首先将元素入队是BFS所惯用的

	VertexNode* retVal = (VertexNode*)malloc(sizeof(VertexNode));
	EdgeNode* cur = (EdgeNode*)malloc(sizeof(EdgeNode));

	while (!QueueEmpty(&queue)) {
		pop(&queue, retVal);
		if (retVal == NULL) {
			exit(0);
		}
		cur = retVal->p_firstAdjEdge; // cur 和 retVal的类型不一致 在给cur赋值时是赋上顶点表的顶点的第一条与之相联系的边的地址
		if (graph->visited[SearchVertexRetIndex(graph, retVal->val)] == 0) {
			printf("%d ", retVal->val);
			graph->visited[SearchVertexRetIndex(graph, retVal->val)] = 1; // 记录该顶点已被访问过
		}
		while (cur) {
			if (graph->visited[cur->adjVertexIndex] == 0) { // 遇到被访问过的顶点不必入栈，接着遍历下一条边
				push(&queue, &(graph->setsOfVertex[cur->adjVertexIndex].val));
			}

			cur = cur->p_nextEdge;
		}
	}
}