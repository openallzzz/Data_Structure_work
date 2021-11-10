#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char VertexDataType; // 顶点所储存数据的类型
typedef int EdgeWeightDataType; // 边的权值类型

// 边结点(的结构)
typedef struct GraphEdgeNode {
	int adjVertexIndex; // 邻接结点的索引
	struct GraphEdgeNode* p_nextEdge; // 下一条边的地址
	EdgeWeightDataType infoOfEdge; // 边的权值
	char* edgeTitle; // 边的标识
}EdgeNode;

// 顶点(的结构)
typedef struct GraphVertexNode {
	VertexDataType* val;
	EdgeNode* p_firstAdjEdge; // 指向第一条邻接该顶点的边
}VertexNode;

// 邻接表所表示的图所包含的信息
typedef struct {
	VertexNode* setsOfVertex; // 每个顶点所表示的关系表
	int vertexNums; // 图中顶点数
	int edgeNums;  // 图中所存在的关系(边)的个数
	int* indegree; // indegree[i] 表示索引为i的顶点的入度
	int* topo; // 记录拓扑排序的线性序列中顶点的索引
	int* happen_earliest; // happen_earliest[i] 表示索引为i的事件最早发生的时间
	int* happen_late; // happen_late[i] 表示索引为i的事件最迟发生的时间
}ALGraph;

typedef struct SqStack {
	VertexNode* bottom; // 栈底指针
	VertexNode* top; // 栈顶指针
	int capacityOfSqStack;
}SqStack; // 辅助栈 -- 存放入度为0的顶点（集）


void BuildALGraph(ALGraph* graph); // 采用邻接表法初始化AOV-网

int SearchVertexRetIndex(ALGraph* graph, VertexDataType* val); // 在图中寻找值为val的顶点的索引

void showALGraph(ALGraph* graph); // 显示邻接表中的信息

void Topo_sort(ALGraph* graph); // 对AOE-网进行拓扑排序

void CriticalPath(ALGraph* graph); // 解决AOE-网的关键路径

void insertVertex(ALGraph* graph, VertexDataType* val); // 插入顶点

void insertEdge(ALGraph* graph, VertexDataType* from_Vertex, VertexDataType* to_Vertex, EdgeWeightDataType weight, char* edgeTitle); // 插入边

void SqStackInit(SqStack* s); // 顺序栈的初始化

void SqStackPushBack(SqStack* s, VertexNode x); // 顺序栈的入栈操作

void SqStackPopBack(SqStack* s, VertexNode* retTopElem); // 顺序栈的出栈操作

int SqStackEmpty(SqStack* s); // 判断栈是否为空
