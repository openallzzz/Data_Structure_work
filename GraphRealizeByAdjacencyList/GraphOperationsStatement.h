#pragma once
#define MAX_VERTEXNUMS 70 // 最大顶点个数

#include <stdio.h>
#include <stdlib.h>

typedef char VertexDataType; // 顶点所储存数据的类型
typedef int EdgeWeightDataType; // 边的权值类型

// 边结点(的结构)
typedef struct GraphEdgeNode {
	int adjVertexIndex; // 邻接结点的索引
	struct GraphEdgeNode* p_nextEdge; // 下一条边的地址
	EdgeWeightDataType infoOfEdge; // 边的信息
}EdgeNode;

// 顶点(的结构)
typedef struct GraphVertexNode {
	VertexDataType val;
	EdgeNode* p_firstAdjEdge; // 指向第一条邻接该顶点的边
}VertexNode;

// 邻接表所表示的图所包含的信息
typedef struct {
	VertexNode* setsOfVertex; // 每个顶点所表示的关系表
	int vertexNums; // 图中顶点数
	int edgeNums;  // 图中所存在的关系(边)的个数
}ALGraph;

void BuildALGraph(ALGraph* graph); // 采用邻接表法构建无向图

int SearchVertexRetIndex(ALGraph* graph, VertexDataType val); // 在图中寻找值为val的顶点的索引

void showALGraph(ALGraph* graph); // 显示邻接表中的信息

