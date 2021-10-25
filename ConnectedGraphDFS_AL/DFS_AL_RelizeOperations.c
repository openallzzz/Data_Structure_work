#define _CRT_SECURE_NO_WARNINGS 1

#include "DFS_AL_Statement.h"

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

// 对无向连通图进行深度优先遍历
void DFS_AL(ALGraph* graph, int startVertexIndex) {
	printf("%d ", graph->setsOfVertex[startVertexIndex].val);
	graph->visited[startVertexIndex] = 1;

	// 当前访问结点的第一个关联点（用边来存储信息）
	EdgeNode* cur = graph->setsOfVertex[startVertexIndex].p_firstAdjEdge;
	while (cur) {
		// 边中储存着当前顶点的邻接顶点（弧头）的索引
		int adjVertexIndex = cur->adjVertexIndex;
		if (graph->visited[adjVertexIndex] == 0) { // 判断当前顶点的邻接顶点是否被访问过
			DFS_AL(graph, adjVertexIndex);  // 没有被访问过就递归访问
		}

		cur = cur->p_nextEdge; // 访问过就判断被访问过的当前边的下一条边,即当前顶点的其他邻接顶点
	}
}