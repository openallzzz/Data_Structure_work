#define _CRT_SECURE_NO_WARNINGS 1

#include "SSSP_DIJ_Statement.h"

// 初始化有向网的结构
void InitGraph(MatrixGraph* Graph, int n) {
	Graph->setsOfVertex = (int*)malloc(sizeof(int) * n);
	memset(Graph->setsOfVertex, 0, sizeof(int) * n);
	Graph->AdjacencyMatrix = (EdgeWeightDataType**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) {
		Graph->AdjacencyMatrix[i] = (EdgeWeightDataType*)malloc(sizeof(EdgeWeightDataType) * n);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Graph->AdjacencyMatrix[i][j] = Override_MAX_INT;
		}
	}

	// flag_IsSpOfVertex[i] 表示源点到索引为i的顶点是否确定了最短距离。  
	// 初始：（false --- 0）
	Graph->flag_IsSpOfVertex = (int*)malloc(sizeof(int) * n);
	memset(Graph->flag_IsSpOfVertex, 0, sizeof(int) * n);

	// indexOfForward[i] 表示源点到索引为i的顶点的最短路径上，顶点i的直接前驱 。
	// 初始：（-1）
	Graph->indexOfForward = (int*)malloc(sizeof(int) * n);
	memset(Graph->indexOfForward, -1, sizeof(int) * n);

	// spOfVertex 表示源点到其他顶点的最短路径。
	// 初始： （无穷---Override_MAX_INT） 
	Graph->spOfVertex = (int*)malloc(sizeof(int) * n);
	memset(Graph->spOfVertex, Override_MAX_INT, sizeof(int) * n);

	Graph->numsOfEdge = 0;
	Graph->numsOfVertex = 0;
	Graph->MaxSizeCnt = n;
}

// 在有向网中插入顶点
void InsertVertex(MatrixGraph* Graph, int vertex) {
		if (Graph->numsOfEdge >= Graph->MaxSizeCnt) exit(0);
		int i = Graph->numsOfVertex;
		Graph->setsOfVertex[i] = vertex;
		Graph->numsOfVertex++;
}

// 添加顶点间的联系
void InsertEdge(MatrixGraph* Graph, int v1, int v2, EdgeWeightDataType weight) {
	Graph->AdjacencyMatrix[v1][v2] = weight;
	Graph->numsOfEdge++;
}

// 显示有向网的邻接矩阵
void ShowMatrix(MatrixGraph* Graph) {
	printf("\n\n\n");
	for (int i = 0; i < Graph->numsOfVertex; i++) {
		printf("       [");
		for (int j = 0; j < Graph->numsOfVertex; j++) {
			if (j != Graph->numsOfVertex - 1) {
				if(Graph->AdjacencyMatrix[i][j] == Override_MAX_INT) printf("00 ");
				else printf("%02d ", Graph->AdjacencyMatrix[i][j]);
			}
			else {
				if (Graph->AdjacencyMatrix[i][j] == Override_MAX_INT) printf("00");
				else printf("%02d", Graph->AdjacencyMatrix[i][j]);
			}
		}
		printf("]");
		printf("\n");
	}
}

// DIJkstra算法解决SSSP问题
void SSSP_DIJ(MatrixGraph* Graph, int v0) {
	int n = Graph->numsOfVertex;

	// 初始化辅助数组	
	for (int i = 0; i < n; i++) {
		Graph->flag_IsSpOfVertex[i] = 0;
		Graph->spOfVertex[i] = Graph->AdjacencyMatrix[v0][i];

		if (Graph->spOfVertex[i] < Override_MAX_INT) Graph->indexOfForward[i] = v0;
		else Graph->indexOfForward[i] = -1;
	}

	Graph->flag_IsSpOfVertex[v0] = 1;
	Graph->spOfVertex[v0] = 0;

	// 每一次寻找当前中转点到其他顶点的最短距离，v0当作成第一次的中转点

	
	for (int i = 0; i < n; i++) {

		int minWeightEdgeDesIndex = 0;
		int min_FLag = Override_MAX_INT;
		for (int j = 0; j < n; j++) {
			if (!Graph->flag_IsSpOfVertex[j] && Graph->spOfVertex[j] < min_FLag) {
				minWeightEdgeDesIndex = j;
				min_FLag = Graph->spOfVertex[j];
			}
		}
		Graph->flag_IsSpOfVertex[minWeightEdgeDesIndex] = 1;

		for (int j = 0; j < n; j++) {
			int flag = (Graph->spOfVertex[minWeightEdgeDesIndex] + Graph->AdjacencyMatrix[minWeightEdgeDesIndex][j]) < Graph->spOfVertex[j];
			if (!Graph->flag_IsSpOfVertex[j] && flag) {
				Graph->spOfVertex[j] = Graph->spOfVertex[minWeightEdgeDesIndex] +
					Graph->AdjacencyMatrix[minWeightEdgeDesIndex][j];
				Graph->indexOfForward[j] = minWeightEdgeDesIndex;
			}
				
		}
	}
	// 打印出源点到每个顶点的最短距离

	for (int i = 0; i < n; i++) {
		if (i == v0) continue;
		printf("源点%d到顶点%d的最短路径为：%02d. 所选择的路径为：", Graph->setsOfVertex[i], Graph->setsOfVertex[v0], 
			Graph->spOfVertex[i]);

		int l = i;
		printf("( %d", Graph->setsOfVertex[l]);
		while (l) {
			l = Graph->indexOfForward[l];
			printf(", %d", Graph->setsOfVertex[l]);
		}
		printf(" )\n");
	}
}