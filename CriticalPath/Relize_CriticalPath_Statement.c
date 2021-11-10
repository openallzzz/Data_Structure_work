#define _CRT_SECURE_NO_WARNINGS 1

#include "CriticalPath_Statement.h"

// 采用邻接表法构建AOE-网
void BuildALGraph(ALGraph* graph) {
	graph->setsOfVertex = (VertexNode*)malloc(sizeof(VertexNode) * 70);
	graph->topo = (int*)malloc(sizeof(int) * 70);
	graph->indegree = (int*)malloc(sizeof(int) * 70);
	graph->happen_late = (int*)malloc(sizeof(int) * 70);
	graph->happen_earliest = (int*)malloc(sizeof(int) * 70);
	for (int i = 0; i < 70; i++) graph->topo[i] = 0;
	for (int i = 0; i < 70; i++) graph->indegree[i] = 0;
	for (int i = 0; i < 70; i++) graph->happen_earliest[i] = 0;
	for (int i = 0; i < 20; i++) graph->happen_late[i] = 0;
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
		printf("	%s -> ", graph->setsOfVertex[i].val);
		cur = graph->setsOfVertex[i].p_firstAdjEdge;
		while (cur != NULL) {
			printf("%s -> ", graph->setsOfVertex[cur->adjVertexIndex].val);
			cur = cur->p_nextEdge;
		}
		printf("NULL\n");
	}
	printf("\n\n");
}

// 插入顶点
void insertVertex(ALGraph* graph, VertexDataType* val) {
	int i = graph->vertexNums;
	graph->setsOfVertex[i].val = val;
	graph->setsOfVertex[i].p_firstAdjEdge = NULL;
	graph->vertexNums++;
}

// 插入边
void insertEdge(ALGraph* graph, VertexDataType* from_Vertex, VertexDataType* to_Vertex, EdgeWeightDataType weight, char* edgeTitle) {
	VertexDataType* v1 = (VertexDataType*)malloc(sizeof(VertexDataType) * 3);
	VertexDataType* v2 = (VertexDataType*)malloc(sizeof(VertexDataType) * 3);
	int v1Index = 0; strcpy(v1, from_Vertex);
	int v2Index = 0; strcpy(v2, to_Vertex);

	v1Index = SearchVertexRetIndex(graph, v1);
	v2Index = SearchVertexRetIndex(graph, v2);

	EdgeNode* newEdgeNode0 = (EdgeNode*)malloc(sizeof(EdgeNode));
	newEdgeNode0->adjVertexIndex = v2Index;
	newEdgeNode0->infoOfEdge = weight;
	newEdgeNode0->edgeTitle = edgeTitle;
	newEdgeNode0->p_nextEdge = graph->setsOfVertex[v1Index].p_firstAdjEdge;
	graph->setsOfVertex[v1Index].p_firstAdjEdge = newEdgeNode0;
}

// 对AOE-网进行拓扑排序
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
		exit(0);
	}
	else {
		printf("AOV-图的拓扑排序的其中一种为：\n");
		for (int i = 0; i < graph->vertexNums; i++) {
			printf("%s ", graph->setsOfVertex[graph->topo[i]]);
		}
		printf("\n");
	}
}

// 解决AOE-网的关键路径
void CriticalPath(ALGraph* graph) {
	Topo_sort(graph);
	printf("\nAOE-网的关键路径为：\n");
	int numsOfVertex = graph->vertexNums;
	// 初始化每个事件的最早发生时间
	for (int i = 0; i < numsOfVertex; i++) {
		graph->happen_earliest[i] = 0;
	}

	// 解决每个事件的最早发生时间
	for (int i = 0; i < numsOfVertex; i++) {
		int indexOfTopoList = graph->topo[i]; // 获取拓扑序列中顶点的索引
		EdgeNode* cur = graph->setsOfVertex[indexOfTopoList].p_firstAdjEdge; // 获取每个顶点所邻接的顶点
		while (cur) {
			int adjVer_Index = cur->adjVertexIndex;
			if (graph->happen_earliest[adjVer_Index] < graph->happen_earliest[indexOfTopoList] + cur->infoOfEdge) {
				graph->happen_earliest[adjVer_Index] = graph->happen_earliest[indexOfTopoList] + cur->infoOfEdge;
			}
			cur = cur->p_nextEdge;
		}
	}

	// 初始化每个事件的最迟发生时间
	for (int i = 0; i < numsOfVertex; i++) {
		int late_times = graph->happen_earliest[numsOfVertex - 1];
		graph->happen_late[i] = late_times;
	}

	// 解决每个事件的最迟发生时间
	for (int i = numsOfVertex - 1; i >= 0; i--) {
		int indexOfTopoList = graph->topo[i];
		EdgeNode* cur = graph->setsOfVertex[indexOfTopoList].p_firstAdjEdge;
		while (cur) {
			int adjVer_index = cur->adjVertexIndex;
			if (graph->happen_late[indexOfTopoList] > graph->happen_late[adjVer_index] - cur->infoOfEdge) {
				graph->happen_late[indexOfTopoList] = graph->happen_late[adjVer_index] - cur->infoOfEdge;
			}
			cur = cur->p_nextEdge;
		}
	}
	
	// 判断哪些活动是关键活动--转化为判断活动所联系的两个事件
	printf("源点 -> ");
	for (int i = 0; i < numsOfVertex; i++) {
		EdgeNode* cur = graph->setsOfVertex[i].p_firstAdjEdge;
		while (cur) {
			int adjVerIndex = cur->adjVertexIndex;
			int e_times = graph->happen_earliest[i];
			int l_times = graph->happen_late[adjVerIndex] - cur->infoOfEdge;
			if (e_times == l_times) {
				printf("%s %s -> ", graph->setsOfVertex[i].val, graph->setsOfVertex[adjVerIndex].val);
			}
			cur = cur->p_nextEdge;
		}
	}
	printf("汇点\n");
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

