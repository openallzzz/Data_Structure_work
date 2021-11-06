#pragma once

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZEOFVERTEX 70
// 图的结点的数据类型为Char
typedef char VertexDataType;
// 边的权值类型为Int
typedef int EdgeWeightDataType;

typedef struct {
	VertexDataType head; // 边的起始点 from
	VertexDataType tail; // 边的的终点 to
	EdgeWeightDataType weight; // 边上的权值
}Edge; // 储存边的信息

typedef struct {
	VertexDataType* setsOfVertex; // 一维数组存储顶点的值
	EdgeWeightDataType** AdjacencyMatrix; // 二维数组表示邻接矩阵
	Edge* Edges; // 储存权值较小的一些边的信息
	int* vertexSet; // 每个顶点的连通分量
	int numsOfVertex; // 顶点的个数
	int numsOfEdge;  // 边的条数
	int MaxSizeCnt; // 限制顶点的最大个数
}MatrixGraph; // 邻接矩阵表示图的结构

void InitGraph(MatrixGraph* Graph, int n); // 初始化图的结构

void InsertVertex(MatrixGraph* Graph, VertexDataType vertex); // 在图中插入顶点

void InsertEdge(MatrixGraph* Graph, int v1, int v2, EdgeWeightDataType weight); // 添加顶点间的联系

void ShowMatrix(MatrixGraph* Graph); // 显示图的邻接矩阵表示

int searchVerIndex(MatrixGraph* Graph, VertexDataType verValue); // 在邻接矩阵中寻找值为verIndex的顶点的索引

void sort_Edges(MatrixGraph* Graph); // 为Edge数组按边的权值大小进行从小到大排序

void Kruskal_MSTRelize(MatrixGraph* Graph); // 借助Kruskal算法构造MST
