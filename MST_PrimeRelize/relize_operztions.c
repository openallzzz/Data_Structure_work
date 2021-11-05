#pragma once

#include "Prim_MST_Statement.h"
	
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

	Graph->flag = (closedge*)malloc(sizeof(closedge) * n);
	Graph->numsOfEdge = 0;
	Graph->numsOfVertex = 0;
	Graph->MaxSizeCnt = n;
}

// 在图中插入顶点
void InsertVertex(MatrixGraph* Graph, VertexDataType vertex) {
	int i = Graph->numsOfVertex;
	if (i < Graph->MaxSizeCnt) {
		Graph->setsOfVertex[i] = vertex;
		(Graph->numsOfVertex)++;
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
				printf("%02d ", Graph->AdjacencyMatrix[i][j]);
			}
			else {
				printf("%02d ", Graph->AdjacencyMatrix[i][j]);
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

int Min(MatrixGraph* Graph) {
	int min = 100, minIndex = 0;
	for (int i = 0; i < Graph->numsOfVertex; i++) {
		if ((Graph->flag[i].lowEdgeWeight != 0) && (Graph->flag[i].lowEdgeWeight < min)) {
			min = Graph->flag[i].lowEdgeWeight;
			minIndex = i;
		}
	}

	return minIndex;
}

// 借助图的邻接矩阵来实现Prim算法
void MST_Prim(MatrixGraph* Graph, VertexDataType vertexValue) {
	MatrixGraph retGraph;
	InitGraph(&retGraph, Graph->numsOfVertex);

	int initIndex = searchVerIndex(Graph, vertexValue);

	// 初始化flag数组，以被选择的顶点作为一个单独的集合，其他的所有点看成另外一个集合
	for (int i = 0; i < Graph->numsOfVertex; i++) {
		InsertVertex(&retGraph, Graph->setsOfVertex[i]);
		if (i == initIndex) { // 所选择的点的到所选择的点无边，权值记为0
			Graph->flag[i].lowEdgeWeight = 0;
		}
		else {
			// 其他点到所被选择的点之间的权值由生成的邻接矩阵可得
			// 由于此时被选择的点为一个单独的集合，且当前状态只有
			// 其一个元素，所以其他点到的邻接矩阵到看作是被选择的
			// 点，因为我们要选择一条具有最权值的边，这条边是与当
			// 前被选择的点相邻接的
			Graph->flag[i].lowAdjVex = vertexValue;
			Graph->flag[i].lowEdgeWeight = Graph->AdjacencyMatrix[initIndex][i];
		} 
	}
	int weights = 0;
	for (int i = 1; i < Graph->numsOfVertex; i++) {
		int minWeightEdgeIndex = Min(Graph);

		// 与最小边相连的顶点值（from）
		VertexDataType vertex_0 = Graph->flag[minWeightEdgeIndex].lowAdjVex;
		// 所选择的最小边指向的顶点（to）
		VertexDataType vertex_1 = Graph->setsOfVertex[minWeightEdgeIndex];

		// 根据最优边得到所选择的两个顶点在图中的索引，重新加入到所要构造的最小生成树中
		int i_1 = searchVerIndex(Graph, vertex_0);
		int i_2 = searchVerIndex(Graph, vertex_1);

		// 逐步构造最小生成树
		InsertEdge(&retGraph, i_1, i_2, Graph->flag[minWeightEdgeIndex].lowEdgeWeight);
		// 累计每次选择的最优边的权值
		weights += Graph->flag[minWeightEdgeIndex].lowEdgeWeight;

		printf("The %d times two vertices selected are：%c %c\n", i, vertex_0, vertex_1);
		(Graph->flag)[minWeightEdgeIndex].lowEdgeWeight = 0;
		// 以当前选择的最小权值的边指向的顶点为基准，更新flag数组
		for (int i = 0; i < Graph->numsOfVertex; i++) {
			int edge_0 = Graph->AdjacencyMatrix[minWeightEdgeIndex][i];
			int edge_1 = Graph->flag[i].lowEdgeWeight;
			if (edge_0 < edge_1) { 
				/*              ----更新flag数组----
				 与基准作比较，如果基准值小于flag数组中储存着的到相应顶点的权值，则
				 更新flag数组中到相应的顶点的最小权值(由贪心思想可知，flag数组储存
				 的是已构造出的部分最小生成树中到未被选择的顶点的最小权值）为基准值
				 */
				(Graph->flag)[i].lowAdjVex = vertex_1;
				(Graph->flag)[i].lowEdgeWeight = edge_0;
			}
		}
	}
	printf("\n");
	// 打印最小生成树的邻接矩阵
	printf("MST generated with Prim is：\n");
	for (int i = 0; i < retGraph.numsOfVertex; i++) {
		for (int j = 0; j < retGraph.numsOfVertex; j++) {
			if (j == 0) {
				printf("\t   [");
			}
			if (retGraph.AdjacencyMatrix[i][j] == 2147483647) {
				// 不直接连通的两个点：简化其之间的权值
				printf("00 ");
			}
			else {
				printf("%02d ", retGraph.AdjacencyMatrix[i][j]);
				
			}
			if (j == retGraph.numsOfVertex - 1) {
				printf("]");
			}
			
		}
		printf("\n");
	}
	printf("Minimum Cost Spanning is: %d", weights);
}