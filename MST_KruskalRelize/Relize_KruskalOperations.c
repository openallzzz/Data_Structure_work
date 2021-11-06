
#pragma once

#include "Kruskal_MST_Statement.h"

// 初始化图的结构
void InitGraph(MatrixGraph* Graph, int n) {
	Graph->setsOfVertex = (VertexDataType*)malloc(sizeof(VertexDataType) * n);
	Graph->AdjacencyMatrix = (EdgeWeightDataType**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		Graph->AdjacencyMatrix[i] = (EdgeWeightDataType*)malloc(sizeof(EdgeWeightDataType) * n);
	}
	if (Graph->AdjacencyMatrix == NULL) {
		exit(0);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Graph->AdjacencyMatrix[i][j] = 2147483647;
		}
	}


	Graph->vertexSet = (int*)malloc(sizeof(int) * n);
	Graph->Edges = (Edge*)malloc(sizeof(Edge) * n * (n - 1) / 2); // 无向图最多n * (n - 1) / 2条边
	Graph->numsOfEdge = 0;
	Graph->numsOfVertex = 0;
	Graph->MaxSizeCnt = n;
}

// 在图中插入顶点
void InsertVertex(MatrixGraph* Graph, VertexDataType vertex) {
	int i = Graph->numsOfVertex;
	Graph->setsOfVertex[i] = vertex; // 录入顶点的信息
	Graph->vertexSet[i] = i; // 开始时给每个顶点的连通分量分配为自己

	(Graph->numsOfVertex)++; // 顶点的个数增加
}

// 添加顶点间的联系
void InsertEdge(MatrixGraph* Graph, int v1, int v2, EdgeWeightDataType weight) {
	Graph->AdjacencyMatrix[v1][v2] = weight;
	Graph->AdjacencyMatrix[v2][v1] = weight;
	Graph->Edges[Graph->numsOfEdge].weight = weight;
	Graph->Edges[Graph->numsOfEdge].head = Graph->setsOfVertex[v1];
	Graph->Edges[Graph->numsOfEdge].tail = Graph->setsOfVertex[v2];

	Graph->numsOfEdge++;
}

// 显示图的邻接矩阵表示
void ShowMatrix(MatrixGraph* Graph) {
	printf("\n\n\n");
	for (int i = 0; i < Graph->numsOfVertex; i++) {
		printf("       [");
		for (int j = 0; j < Graph->numsOfVertex; j++) {
			if (j == 0) {
				if (Graph->AdjacencyMatrix[i][j] == 2147483647) printf("00 ");
				else printf("%02d ", Graph->AdjacencyMatrix[i][j]);
				continue;
			}
			if (j != Graph->numsOfVertex - 1) {
				if (Graph->AdjacencyMatrix[i][j] == 2147483647) printf("00 ");
				else printf("%02d ", Graph->AdjacencyMatrix[i][j]);
			}
			else {
				if (Graph->AdjacencyMatrix[i][j] == 2147483647) printf("00");
				else printf("%02d", Graph->AdjacencyMatrix[i][j]);
			}
		}
		printf("]");
		printf("\n");
	}
}

// 在邻接矩阵中寻找值为verIndex的顶点的索引
int searchVerIndex(MatrixGraph* Graph, VertexDataType verValue) {
	for (int i = 0; i < Graph->numsOfVertex; i++) {
		if (verValue == Graph->setsOfVertex[i]) {
			return i;
		}
	}

	return -1;
}

// 为Edges数组按边的权值大小进行从小到大排序
void sort_Edges(MatrixGraph* Graph) {
	for (int i = 0; i < Graph->numsOfEdge - 1; i++) {
		for (int j = 0; j < Graph->numsOfEdge - i - 1; j++) {
			if (Graph->Edges[j].weight > Graph->Edges[j + 1].weight) {
				Edge tmp = Graph->Edges[j];
				Graph->Edges[j] = Graph->Edges[j + 1];
				Graph->Edges[j + 1] = tmp;
			}
		}
	}
}

// 借助Kruskal算法构造MST
void Kruskal_MSTRelize(MatrixGraph* Graph) {
	sort_Edges(Graph);

	MatrixGraph KruskalMST;
	InitGraph(&KruskalMST, Graph->numsOfVertex);

	for (int i = 0; i < Graph->numsOfVertex; i++)
		InsertVertex(&KruskalMST, Graph->setsOfVertex[i]);

	int cnt = 1;
	for (int i = 0; i < Graph->numsOfEdge; i++) {
		int v1 = searchVerIndex(Graph, Graph->Edges[i].head);
		int v2 = searchVerIndex(Graph, Graph->Edges[i].tail);

		int v1_Adj = Graph->vertexSet[v1];
		int v2_Adj = Graph->vertexSet[v2];

		if (v1_Adj != v2_Adj) {
			InsertEdge(&KruskalMST, v1, v2, Graph->Edges[i].weight);
			printf("The two vertices of the %d selected edge are: %c %c\n", cnt++ , Graph->Edges[i].head, Graph->Edges[i].tail);
			for (int j = 0; j < Graph->numsOfVertex; j++) {
				if (Graph->vertexSet[j] == v2_Adj) Graph->vertexSet[j] = v1_Adj;
			}
		}
	}

	printf("\n\nThe MST generated with the Kruskal algorithm is:\n");
	ShowMatrix(&KruskalMST);
}