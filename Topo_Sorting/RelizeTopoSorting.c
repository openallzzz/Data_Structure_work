#define _CRT_SECURE_NO_WARNINGS 1

#include "Topo_sortingStatement.h"

// 采用邻接表法构建无向图
void BuildALGraph(ALGraph* graph) {
	graph->setsOfVertex = (VertexNode*)malloc(sizeof(VertexNode) * 70);
	graph->topo = (int*)malloc(sizeof(int) * 70);
	graph->indegree = (int*)malloc(sizeof(int) * 70);
	memset(graph->indegree, 0, sizeof(int) * 70);
	memset(graph->topo, 0, sizeof(int) * 70);
	graph->edgeNums = 0;
	graph->vertexNums = 0;
}

// 在图中寻找值为val的顶点的索引
int SearchVertexRetIndex(ALGraph* graph, VertexDataType* val) {

	for (int i = 0; i < graph->vertexNums; i++) {
		if (!strcmp(graph->setsOfVertex[i].val, val)) {
			return i;
		}
	}

	return -1;
}

// 显示邻接表中的信息
void showALGraph(ALGraph* graph) {
	EdgeNode* cur = NULL;
	printf("AOV-网的邻接表：\n\n");
	for (int i = 0; i < graph->vertexNums; i++) {
		printf("	%s->", graph->setsOfVertex[i].val);
		cur = graph->setsOfVertex[i].p_firstAdjEdge;
		while (cur != NULL) {
			printf("%s->", graph->setsOfVertex[cur->adjVertexIndex].val);
			cur = cur->p_nextEdge;
		}
		printf("NULL\n");
	}
	printf("\n\n");
}

// 插入顶点
void insertVertex(ALGraph* graph, VertexDataType* val){
	int i = graph->vertexNums;
	graph->setsOfVertex[i].val = val;
	graph->setsOfVertex[i].p_firstAdjEdge = NULL;
	graph->vertexNums++;
}

// 插入边
void insertEdge(ALGraph* graph, VertexDataType* from_Vertex, VertexDataType* to_Vertex, EdgeWeightDataType weight) {
	VertexDataType* v1 = (VertexDataType*)malloc(sizeof(VertexDataType) * 3);
	VertexDataType* v2 = (VertexDataType*)malloc(sizeof(VertexDataType) * 3);
	int v1Index = 0; strcpy(v1, from_Vertex);
	int v2Index = 0; strcpy(v2, to_Vertex);

	v1Index = SearchVertexRetIndex(graph, v1);
	v2Index = SearchVertexRetIndex(graph, v2);

	EdgeNode* newEdgeNode0 = (EdgeNode*)malloc(sizeof(EdgeNode));
	newEdgeNode0->adjVertexIndex = v2Index;
	newEdgeNode0->infoOfEdge = weight;
	newEdgeNode0->p_nextEdge = graph->setsOfVertex[v1Index].p_firstAdjEdge;
	graph->setsOfVertex[v1Index].p_firstAdjEdge = newEdgeNode0;
}

// 对AOV-网进行拓扑排序
void Topo_sort(ALGraph* graph) {
	// 借助graph中的indegree数组记录每个顶点的入度
	for (int i = 0; i < graph->vertexNums; i++) {
		EdgeNode* cur = graph->setsOfVertex[i].p_firstAdjEdge;
		while (cur) {
			int j = cur->adjVertexIndex;
			graph->indegree[j]++;
			cur = cur->p_nextEdge;
		}
	}

	// 初始化辅助栈
	SqStack s;
	SqStackInit(&s);

	for (int i = 0; i < graph->vertexNums; i++) {
		if (!graph->indegree[i]) {
			SqStackPushBack(&s, graph->setsOfVertex[i]);
		}
	}

	int cnt_inputed_Vertex = 0; // 设置计数器记录已经输出的顶点数
	while (!SqStackEmpty(&s)) {
		VertexNode top_Vertex;
		SqStackPopBack(&s, &top_Vertex);

		int top_Vertex_index = SearchVertexRetIndex(graph, top_Vertex.val);
		graph->topo[cnt_inputed_Vertex] = top_Vertex_index;
		cnt_inputed_Vertex++;

		EdgeNode* p_fristAdjEdgeOfTop_vertex = top_Vertex.p_firstAdjEdge;
		while (p_fristAdjEdgeOfTop_vertex) {
			int indexOfAdjVertex = p_fristAdjEdgeOfTop_vertex->adjVertexIndex;
			graph->indegree[indexOfAdjVertex]--;
			if (graph->indegree[indexOfAdjVertex] == 0) {
				SqStackPushBack(&s, graph->setsOfVertex[indexOfAdjVertex]);
			}
			p_fristAdjEdgeOfTop_vertex = p_fristAdjEdgeOfTop_vertex->p_nextEdge;
		}
	}
	if (cnt_inputed_Vertex < graph->vertexNums) {
		printf("AOV-图中有环，无法进行拓扑排序\n");
	}
	else {
		printf("AOV-图的拓扑排序的其中一种为：\n");
		for (int i = 0; i < graph->vertexNums; i++) {
			printf("%s ", graph->setsOfVertex[graph->topo[i]]);
		}
	}
}

// 顺序栈的初始化
void SqStackInit(SqStack* s) {
	s->bottom = (VertexNode*)malloc(sizeof(VertexNode) * 70);
	if (!s->bottom) exit(0);
	s->top = s->bottom;
	s->capacityOfSqStack = 70;
}

// 顺序栈的入栈操作
void SqStackPushBack(SqStack* s, VertexNode x) {
	if (s->top - s->bottom == 70) {
		exit(0);
	}

	*(s->top) = x;
	s->top++;

}

// 顺序栈的出栈操作
void SqStackPopBack(SqStack* s, VertexNode* retTopElem) {
	if (SqStackEmpty(s)) exit(0);

	*retTopElem = *(s->top - 1);
	s->top--;
}

// 判断栈是否为空
int SqStackEmpty(SqStack* s) {
	if (s->bottom == s->top) return 1;

	return 0;
}