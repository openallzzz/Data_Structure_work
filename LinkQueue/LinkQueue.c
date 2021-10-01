#define _CRT_SECURE_NO_WARNINGS 

#include <stdio.h>
#include <stdlib.h>

// 重命名链式队列的数据域的类型
typedef int LqueueDatatype;

typedef struct queueNode
{
	LqueueDatatype data;
	struct queueNode* next;
}LqueueNode; // 链式队列的结点

typedef struct
{
	LqueueNode* head;
	LqueueNode* tail;
}LinkQueue; // 链式队列

LqueueNode* BuyNewQueueNode(LqueueDatatype x); // 创建一个新结点并返回
void LinkQueueInit(LinkQueue* q); // 链式队列的初始化 
void LinkQueuePushBack(LinkQueue* q, LqueueDatatype x); // 链式队列的入队操作
void LinkQueuePopFront(LinkQueue* q, LqueueDatatype* retData); // 链式队列的出队操作
void LinkQueuePrint(LinkQueue* q); // 打印链式队列
LqueueDatatype LinkQueueGetTop(LinkQueue* q); // 获取队头元素

int main()
{
	LinkQueue q;
	LqueueDatatype ret = 0;
	LinkQueueInit(&q);
	LinkQueuePushBack(&q, 5);
	LinkQueuePushBack(&q, 7);
	LinkQueuePushBack(&q, 1);
	LinkQueuePushBack(&q, 6);
	LinkQueuePushBack(&q, 2);
	LinkQueuePrint(&q);
	LinkQueuePopFront(&q, &ret);
	LinkQueuePrint(&q); 
	printf("%d\n", ret);
	return 0;
}

LqueueNode* BuyNewQueueNode(LqueueDatatype x) // 创建一个新结点并返回
{
	LqueueNode* newNode = (LqueueNode*)malloc(sizeof(LqueueNode));
	newNode->data = x;
	newNode->next = NULL;
	return newNode;
}
void LinkQueueInit(LinkQueue* q) // 初始化链式队列
{
	// 创建一个结点将其作为头指针和尾指针的结点
	LqueueNode* newNode = (LqueueNode*)malloc(sizeof(LqueueNode));
	newNode->next = NULL;
	// 赋值操作
	q->head = q->tail = newNode;
}

void LinkQueuePushBack(LinkQueue* q, LqueueDatatype x) // 链式队列的入队操作
{
	LqueueNode* newNode = BuyNewQueueNode(x);
	q->tail->next = newNode;
	q->tail = newNode;
}

void LinkQueuePopFront(LinkQueue* q, LqueueDatatype* retData) // 链式队列的出队操作
{
	if (q->head == q->tail)
	{
		printf("出队失败，目前队列中无数据");
		return;
	}
	LqueueNode* pHeadNow = q->head->next; // 保存当前队列中的队头结点
	*retData = pHeadNow->data; // 保存当前队头结点的数据

	// 下面完成删除操作
	q->head->next = pHeadNow->next;

	// 如果删除的结点为当前队列中最后一个结点时
	// 此时队尾结点也需要改变
	if (q->tail = pHeadNow)
	{
		q->tail = q->head;
	}
	free(pHeadNow);
}

void LinkQueuePrint(LinkQueue* q) // 打印链式队列
{
	LqueueNode* phead = q->head->next;
	while (phead)
	{
		printf("%d->", phead->data);
		phead = phead->next;
	}
	printf("NULL\n");
}
LqueueDatatype LinkQueueGetTop(LinkQueue* q) // 获取队头元素
{
	if (q->head == q->tail)
	{
		printf("当前队列中无数据");
		exit(0);
	}

	return q->head->next->data;
}