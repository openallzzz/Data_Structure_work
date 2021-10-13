#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>


typedef char BTDataType;

typedef struct BinaryTreeNode
{
	struct BinaryTreeNode* LeftNode;
	struct BinaryTreeNode* RightNode;
	BTDataType val;
}BTNode;

// 构建链式队列的结点
typedef BTNode* LQueueData; // 将二叉树结点的地址设为队列的值

typedef struct LQueueNode
{
	LQueueData val;
	struct LQueueNode* next;
}LQueueNode;

// 构建链式队列
typedef struct
{
	LQueueNode* Head;
	LQueueNode* Tail;
}LinkQueue;

// 创建队列结点并返回其指针
LQueueNode* BuyNewLqueueNode(LQueueData val) {
	LQueueNode* newNode = (LQueueNode*)malloc(sizeof(LQueueNode));
	if (newNode == NULL) {
		exit(0);
	}

	newNode->val = val;
	newNode->next = NULL;
}
// 初始化链式队列
void InitLinkQueue(LinkQueue* s) {
	LQueueNode* pHead = (LQueueNode*)malloc(sizeof(LQueueNode));
	if (pHead == NULL) {
		exit(0);
	}
	pHead->next = NULL;

	s->Head = pHead;
	s->Tail = pHead;
}
// 队列判空
int LQueueEmpty(LinkQueue* s) {
	if (s->Head == s->Tail) {
		return 1;
	}
	return 0;
}
// 入队
void LQueuePush(LinkQueue* s, LQueueData val) {
	LQueueNode* newNode = BuyNewLqueueNode(val);
	if (newNode == NULL) {
		exit(0);
	}
	(s->Tail)->next = newNode;
	s->Tail = newNode;
}
// 出队操作
void LQueuePop(LinkQueue* s, LQueueNode* retNode) {
	if (LQueueEmpty(s)) {
		return;
	}

	LQueueNode* pHead = s->Head->next;
	*retNode = *pHead;
	s->Head->next = pHead->next;
	if (pHead == s->Tail) {
		s->Tail = s->Head;
	}
}

void TreeSize(BTNode* root, int* size) {
	if (root == NULL) {
		return;
	}

	(*size)++;
	TreeSize(root->LeftNode, size);
	TreeSize(root->RightNode, size);

	// 分治:: ---
	//return root == NULL ? 0 : TreeSize(root-LeftNode) + TreeSize(root->Right) + 1;
}

// 二叉树叶子的个数

int TreeLeafSize(BTNode* root) {
	/*return (root->LeftNode == NULL && root->RightNode == NULL) ? 1 : TreeLeafSize(root->LeftNode)
		+ TreeLeafSize(root->RightNode);*/

	if (root == NULL) {
		return 0;
	}

	if (root->LeftNode == NULL && root->RightNode == NULL) {
		return 1;
	}

	return TreeLeafSize(root->LeftNode) + TreeLeafSize(root->RightNode);
}

// 层次遍历 广度优先遍历 一般用到队列
void LevelOrder(BTNode* root) {
	LinkQueue q;
	InitLinkQueue(&q);
	if (root) {
		LQueuePush(&q, root);
	}

	while (!LQueueEmpty(&q)) {
		LQueueNode retNode;
		LQueuePop(&q, &retNode);
		printf("%c", retNode.val->val);

		if ((&retNode)->val->LeftNode) {
			LQueuePush(&q, (&retNode)->val->LeftNode);
		}

		if ((&retNode)->val->RightNode) {
			LQueuePush(&q, (&retNode)->val->RightNode);
		}
	}

	printf("\n");
}


int main()
{
	BTNode* A = (BTNode*)malloc(sizeof(BTNode));
	A->LeftNode = NULL;
	A->RightNode = NULL;
	A->val = 'A';

	BTNode* B = (BTNode*)malloc(sizeof(BTNode));
	B->LeftNode = NULL;
	B->RightNode = NULL;
	B->val = 'B';

	BTNode* C = (BTNode*)malloc(sizeof(BTNode));
	C->LeftNode = NULL;
	C->RightNode = NULL;
	C->val = 'C';

	BTNode* D = (BTNode*)malloc(sizeof(BTNode));
	D->LeftNode = NULL;
	D->RightNode = NULL;
	D->val = 'D';

	BTNode* E = (BTNode*)malloc(sizeof(BTNode));
	E->LeftNode = NULL;
	E->RightNode = NULL;
	E->val = 'E';

	A->LeftNode = B;
	A->RightNode = C;
	B->LeftNode = D;
	B->RightNode = E;

	int sizeA = 0;
	TreeSize(A, &sizeA);
	printf("\nA TreeSize is %d\n", sizeA);

	int sizeB = 0;
	TreeSize(B, &sizeB);
	printf("B TreeSize is %d\n", sizeB);

	printf("A TreeLeafSize is %d\n", TreeLeafSize(A));
	printf("B TreeLeafSize is %d\n", TreeLeafSize(B));

	LevelOrder(A);
	LevelOrder(C);
	return 0;
}