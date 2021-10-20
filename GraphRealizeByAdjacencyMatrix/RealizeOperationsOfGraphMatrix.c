#define _CRT_SECURE_NO_WARNINGS 1

#include "StatementGraphStructure.h"

// 初始化图的结构
void InitGraph(MatrixGraph* Graph, int n) {
	Graph->setsOfVertex = (VertexDataType*)malloc(sizeof(VertexDataType) * n);
	Graph->AdjacencyMatrix = (EdgeWeightDataType**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		Graph->AdjacencyMatrix[i] = (EdgeWeightDataType*)malloc(sizeof(EdgeWeightDataType) * n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Graph->AdjacencyMatrix[i][j] = 0;
		}
	}
	Graph->numsOfEdge = 0;
	Graph->numsOfVertex = 0;
	Graph->MaxSizeCnt = n;
}

// 在图中插入顶点
void InsertVertex(MatrixGraph* Graph, VertexDataType vertex) {
	if (Graph->numsOfVertex <= Graph->MaxSizeCnt) {
		Graph->setsOfVertex[Graph->numsOfEdge] = vertex;
		Graph->numsOfVertex++;
	}
}

// 添加顶点间的联系
void InsertEdge(MatrixGraph* Graph, int v1, int v2, EdgeWeightDataType weight) {
	Graph->AdjacencyMatrix[v1][v2] = weight;
	Graph->AdjacencyMatrix[v2][v1] = weight;
	Graph->numsOfEdge++;
}

// 显示图的邻接矩阵表示
void ShowMatrix(MatrixGraph* Graph) {
	printf("\n\n\n");
	for (int i = 0; i < Graph->numsOfVertex; i++) {
		printf("       [ ");
		for (int j = 0; j < Graph->numsOfVertex; j++) {
			if (j != Graph->numsOfVertex - 1) {
				printf("%d ", Graph->AdjacencyMatrix[i][j]);
			}
			else {
				printf("%d ", Graph->AdjacencyMatrix[i][j]);
			}
		}
		printf("]");
		printf("\n");
	}
}