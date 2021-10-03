#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char name[10];
	int sex; // 说明： 0-表示女孩，1-表示男孩
}Person;   // 定义本题中一个人的结构

typedef struct LQueueNode
{
	Person data;
	struct LQueueNode* next;
}LQueueNode;  // 定义链式队列中结点的结构

typedef struct
{
	LQueueNode* head;
	LQueueNode* tail;
}LinkQueue;  // 定义链式队列的结构

LQueueNode* BuyNewLQueueNode(char* name, int sex); // 构造一个新结点   Ps:不单独使用该函数 在入队操作中嵌套使用
void LinkQueueInit(LinkQueue* q); // 初始化链式队列
void LinkQueuePushBack(LinkQueue* q, char* name, int sex); // 链式队列的入队操作
void LinkQueuePopFront(LinkQueue* q, char** retName, int* retSex); // 链式队列的出队操作

int main()
{
	LinkQueue male;
	LinkQueue female;
	LinkQueueInit(&male);
	LinkQueueInit(&female);
	int cnt = 0;
	Person Persons[7] = { {"李明", 1},
		              {"赵红", 0},
	               {"小张", 1},
	            {"张霏", 0},
			 {"赵四", 1},
	      {"红月", 0},
		{"小丽", 0}};

	for (int i = 0; i < 7; i++) // 信息录入
	{
		if (Persons[i].sex == 0) // 性别为女
		{
			LinkQueuePushBack(&female, Persons[i].name, Persons[i].sex);
		}
		else  // 性别为男
		{
			LinkQueuePushBack(&male, Persons[i].name, Persons[i].sex);
		}
	}

	while (male.head != male.tail && female.head != female.tail)
	{
		cnt++;
		
		char* maleName = (char*)malloc(sizeof(char) * 10);
		char* femaleName = (char*)malloc(sizeof(char) * 10);
		if (maleName == NULL || femaleName == NULL)
		{
			printf("申请内存时出错");
			exit(0);
		}
		
		int maleSex;
		int femaleSex;
		LinkQueuePopFront(&male, &maleName, &maleSex);
		LinkQueuePopFront(&female, &femaleName, &femaleSex);
		printf("第%d对：男：%s, 女：%s\n", cnt, maleName, femaleName);
	}
	if (female.head == female.tail)
	{
		printf("下一次舞曲开始时,获得优先匹配权的是：男同学,%s\n", male.head->next->data.name);
	}
	else
	{
		printf("下一次舞曲开始时,获得优先匹配权的是：女同学,%s\n", female.head->next->data.name);
	}
	return 0;
}

LQueueNode* BuyNewLQueueNode(char* name, int sex) // 构造一个新结点
{
	LQueueNode* newNode = (LQueueNode*)malloc(sizeof(LQueueNode));
	if (newNode == NULL)
	{
		printf("申请内存失败");
		return NULL;
	}

	strcpy(newNode->data.name, name);
	newNode->data.sex = sex;
	newNode->next = NULL;
}

void LinkQueueInit(LinkQueue* q) // 初始化链式队列
{
	LQueueNode* newNode = (LQueueNode*)malloc(sizeof(LQueueNode));
	if (newNode == NULL)
	{
		printf("申请内存失败");
		exit(0);
	}

	newNode->next = NULL;
	q->head = newNode;
	q->tail = newNode;
}
void LinkQueuePushBack(LinkQueue* q, char* name, int sex) // 链式队列入队操作
{
	LQueueNode* newNode = BuyNewLQueueNode(name, sex);
	q->tail->next = newNode;
	q->tail = newNode;
}
void LinkQueuePopFront(LinkQueue* q, char** retName, int* retSex) // 链式队列的出队操作
{
	if (q->head == q->tail)
	{
		printf("该队列空间为空，无法出队");
		exit(0);
	}

	LQueueNode* nowPhead = q->head->next;
	strcpy(*retName, nowPhead->data.name);
	*retSex = nowPhead->data.sex;

	q->head->next = nowPhead->next; // 注意代码的正确性
	if (nowPhead == q->tail)
	{
		q->tail = q->head;
	}
	free(nowPhead);
}