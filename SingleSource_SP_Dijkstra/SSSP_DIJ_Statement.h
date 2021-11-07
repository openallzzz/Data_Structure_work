#pragma once

#include <stdio.h>
#include <stdlib.h>
#define Override_MAX_INT 20020427

// 图的结点的数据类型为Char
//typedef int VertexDataType;
// 边的权值类型为Int
typedef int EdgeWeightDataType;

typedef struct {
	int* setsOfVertex; // 一维数组存储顶点的值
	EdgeWeightDataType** AdjacencyMatrix; // 二维数组表示邻接矩阵
	int* flag_IsSpOfVertex; // 记录从源点到其他顶点是否已经被确定最短路径
	int* indexOfForward; // 记录源点到其他顶点的最短路径上该顶点的直接前驱
	int* spOfVertex; // 记录源点到其他顶点的最短路径的长度
	int numsOfVertex; // 顶点的个数
	int numsOfEdge;  // 边的条数
	int MaxSizeCnt; // 限制顶点的最大个数
}MatrixGraph; // 邻接矩阵表示图的结构

void InitGraph(MatrixGraph* Graph, int n); // 初始化图的结构

void InsertVertex(MatrixGraph* Graph, int vertex); // 在图中插入顶点

void InsertEdge(MatrixGraph* Graph, int v1, int v2, EdgeWeightDataType weight); // 添加顶点间的联系

void ShowMatrix(MatrixGraph* Graph); // 显示图的邻接矩阵表示

void SSSP_DIJ(MatrixGraph* Graph, int v0); // DIJkstra算法解决SSSP问题
