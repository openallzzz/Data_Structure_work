#pragma once

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZEOFVERTEX 70
// 图的结点的数据类型为Char
typedef char VertexDataType;
// 边的权值类型为Int
typedef int EdgeWeightDataType;

typedef struct {
	VertexDataType lowAdjVex; // 与最小边相邻接的顶点的值
	EdgeWeightDataType lowEdgeWeight; // 最小边的权值
}closedge;

typedef struct {
	VertexDataType* setsOfVertex; // 一维数组存储顶点的值
	EdgeWeightDataType** AdjacencyMatrix; // 二维数组表示邻接矩阵
	closedge* flag; // 标记数组
	int numsOfVertex; // 顶点的个数
	int numsOfEdge;  // 边的条数
	int MaxSizeCnt; // 限制顶点的最大个数
}MatrixGraph; // 邻接矩阵表示图的结构

void InitGraph(MatrixGraph* Graph, int n); // 初始化图的结构

void InsertVertex(MatrixGraph* Graph, VertexDataType vertex); // 在图中插入顶点

void InsertEdge(MatrixGraph* Graph, int v1, int v2, EdgeWeightDataType weight); // 添加顶点间的联系

void ShowMatrix(MatrixGraph* Graph); // 显示图的邻接矩阵表示

int searchVerIndex(MatrixGraph* Graph, VertexDataType verValue); // 在邻接矩阵中寻找值为verIndex的顶点的索引

int Min(MatrixGraph* Graph); // 在辅助数组中寻找最小边，目的是添加顶点

void MST_Prim(MatrixGraph* Graph, VertexDataType vertexValue); // 借助图的邻接矩阵来实现Prim算法