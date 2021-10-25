#pragma once

#include "ConnectedGraphBFS_ALStatement.h"
typedef struct LQueueNode {
	VertexNode* val; // 队列中存放图中的顶点
	struct LQueueNode* next;
}LQueueNode;

typedef struct {
	LQueueNode* head;
	LQueueNode* tail;
}LQueue;

void InitLQueue(LQueue* queue); // 初始化链式队列

void push(LQueue* queue, VertexNode* val); // 队列的入队操作

void pop(LQueue* queue, VertexNode* retVertex); // 队列的出队操作

int QueueEmpty(LQueue* queue); // 判断队列是否为空
