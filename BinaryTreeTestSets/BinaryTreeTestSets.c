#define _CRT_SECURE_NO_WARNINGS 1
typedef char BinTreeData;

#include <stdio.h>
#include <stdlib.h>

// 定义二叉树的结点结构（储存结构）
typedef struct BinaryTreeNode {
	BinTreeData val; // 数据域

	// 指向左右子树树根的指针域
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;

}BTNode;

typedef struct SeqStack {
	BTNode* top;
	BTNode* bottom;
	int SeqStackCapacity;
}SqStack; // 定义顺序栈的存储结构

typedef struct QueueNode {
	BTNode* val;
	struct QueueNode* next;
}QNode;

typedef struct {
	QNode* head;
	QNode* tail;
}LQueue;

/*-----------------借助队列实现层序遍历--------------------*/
//  初始化队列
void InitQueue(LQueue* q);

//  入队操作
void QueuePush(LQueue* q, BTNode* val);

//  返回一个队列结点
QNode* BuyNewNode(BTNode* val);

//  出队操作
void QueuePop(LQueue* q, QNode* ret);

//  判断队空
int QueueEmpty(LQueue* q);

/*----------借助栈实现非递归遍历二叉树----------------*/
//  初始化顺序栈
void InitStack(SqStack* s);

//  入栈操作
void StackPush(SqStack* s, BTNode* data);

//  出栈操作
void StackPop(SqStack* s);

//  判断栈空
int StackEmpty(SqStack* s);

//  获取栈顶元素
BTNode* StackGetTop(SqStack* s);


/*---------------二叉树的操作集--------------------*/
//  根据前序序列构建二叉树
BTNode* PrevOrderCreateTree(char* str, int* index);

//  前序遍历二叉树--递归
void PrevOrderByRecursion(BTNode* root);

//  中序遍历二叉树--递归
void InOrderByRecursion(BTNode* root);

//  后序遍历二叉树--递归
void PostOrderByRecursion(BTNode* root);

//  前序遍历二叉树--非递归
void PrevOrderNoRecursion(BTNode* root);

//  中序遍历二叉树--非递归
void InOrderNoRecursion(BTNode* root);

//  计算二叉树中叶子结点的个数
int BTreeLeafSize(BTNode* root);

//  计算二叉树的最大深度 -- 也称二叉树的深度
int maxDepthTree(BTNode* root);

//  二叉树的层序遍历
void LevelOrder(BTNode* root);

int main() {
	/*
	测试的二叉树为：
					A
				   / \
				  B   C
				   \ / \
				   F D E
				  / \
				 G   H
	该二叉树的前序序列为：AB#FG##H##CD##E##
	*/

	char str[100] = "AB#FG##H##CD##E##";
	int i = 0;

	// 借助 root 接收构建成功的二叉树根结点的指针
	BTNode* root = PrevOrderCreateTree(str, &i);
	printf("测试的二叉树为：\n");
	printf("   A   \n");
	printf("  / \\\n");
	printf(" B   C\n");
	printf("  \\ / \\\n");
	printf("  F D E\n");
	printf(" / \\\n");
	printf("G   H\n");
	printf("1.前序遍历-递归：");
	PrevOrderByRecursion(root);
	printf("\n\n2.中序遍历-递归：");
	InOrderByRecursion(root);
	printf("\n\n3.后序遍历-递归：");
	PostOrderByRecursion(root);
	printf("\n\n4.前序遍历-非递归：");
	PrevOrderNoRecursion(root);
	printf("\n5.中序遍历-非递归：");
	InOrderNoRecursion(root);
	int leafCnt = BTreeLeafSize(root);
	printf("\n6.树的叶子结点数：%d\n", leafCnt);
	int treeDepth = maxDepthTree(root);
	printf("\n7. 树的深度：%d\n", treeDepth);
	printf("\n8. 树的层序遍历：");
	LevelOrder(root);

	printf("\n\n");
	return 0;
}

//  根据前序序列构建二叉树
BTNode* PrevOrderCreateTree(char* str, int* pi) {
	if (str[*pi] == '#') {
		(*pi)++;
		return NULL;
	}

	BTNode* root = (BTNode*)malloc(sizeof(BTNode));
	if (root == NULL) {
		printf("内存访问失败\n");
		exit(0);
	}

	root->val = str[*pi];
	(*pi)++;
	root->left  = PrevOrderCreateTree(str, pi);
	root->right = PrevOrderCreateTree(str, pi);

	return root;
}

//  前序遍历二叉树--递归
void PrevOrderByRecursion(BTNode* root) {
	if (root == NULL) {
		return;
	}
	printf("%c ", root->val);
	PrevOrderByRecursion(root->left);
	PrevOrderByRecursion(root->right);
}

//  中序遍历二叉树--递归
void InOrderByRecursion(BTNode* root) {
	if (root == NULL) {
		return;
	}
	InOrderByRecursion(root->left);
	printf("%c ", root->val);
	InOrderByRecursion(root->right);
}

//  后序遍历二叉树--递归
void PostOrderByRecursion(BTNode* root) {
	if (root == NULL) {
		return;
	}
	PostOrderByRecursion(root->left);
	PostOrderByRecursion(root->right);
	printf("%c ", root->val);
}

//  前序遍历二叉树--非递归
void PrevOrderNoRecursion(BTNode* root) {
	SqStack s;
	InitStack(&s);
	StackPush(&s, root);
	BTNode* cur = (BTNode*)malloc(sizeof(BTNode));
	while (!StackEmpty(&s)) {
		cur = StackGetTop(&s);
		StackPop(&s);
		if (cur != NULL) {
			printf("%c ", cur->val);
		}
		else {
			continue;
		}
		BTNode* right = cur->right;
		BTNode* left = cur->left;
		if (right) {
			StackPush(&s, right);
		}
		if (left) {
			StackPush(&s, left);
		}
	}
	printf("\n");
}

//  中序遍历二叉树--非递归
void InOrderNoRecursion(BTNode* root) {
	SqStack s;
	InitStack(&s);
	BTNode* cur = root;
	while (cur != NULL || !StackEmpty(&s)) {
		if (cur) {
			StackPush(&s, cur);
			cur = cur->left;
		}
		else{
			cur = StackGetTop(&s);
			StackPop(&s);
			printf("%c ", cur->val);
			cur = cur->right;
		}
	}
	printf("\n");
}

//  初始化顺序栈
void InitStack(SqStack* s) {
	s->bottom = (BTNode*)malloc(sizeof(BTNode) * 100);
	if (s->bottom == NULL) {
		exit(0);
	}
	s->top = s->bottom;
	s->SeqStackCapacity = 100;
}

//  入栈操作
void StackPush(SqStack* s, BTNode* data) {
	if (s->top - s->bottom == s->SeqStackCapacity) {
		exit(0);
	}
	*(s->top) = *data;
	s->top++;
}

//  出栈操作
void StackPop(SqStack* s) {
	if (s->top == s->bottom) {
		exit(0);
	}
	s->top--;
}

//  判断栈空
int StackEmpty(SqStack* s) {
	if (s->top == s->bottom) {
		return 1;
	}
	return 0;
}

//  获取栈顶元素
BTNode* StackGetTop(SqStack* s) {
	if (s->top == s->bottom) {
		exit(0);
	}

	return s->top - 1;
}

//  计算二叉树中叶子结点的个数
int BTreeLeafSize(BTNode* root) {
	if (root == NULL) {
		return 0;
	}
	
	return (root->left == NULL && root->right == NULL) ? 1 : BTreeLeafSize(root->left)
		+ BTreeLeafSize(root->right);
}

//  计算二叉树的最大深度
int maxDepthTree(BTNode* root) {
	if (root == NULL) {
		return 0;
	}

	int leftDepth = maxDepthTree(root->left);
	int rightDepth = maxDepthTree(root->right);
	return (leftDepth > rightDepth) ? leftDepth + 1 :
		rightDepth + 1;
}

//  初始化队列
void InitQueue(LQueue* q) {
	QNode* pHead = (QNode*)malloc(sizeof(QNode*));
	if (pHead == NULL) {
		exit(0);
	}
	pHead->next = NULL;
	q->head = pHead;
	q->tail = pHead;
}

//  入队操作
void QueuePush(LQueue* q, BTNode* val) {
	QNode* newNode = BuyNewNode(val);
	q->tail->next = newNode;
	q->tail = newNode;
}

//  返回一个结点
QNode* BuyNewNode(BTNode* val) {
	QNode* newNode = (QNode*)malloc(sizeof(QNode));
	if (newNode == NULL) {
		exit(0);
	}
	newNode->val = val;
	newNode->next = NULL;

	return newNode;
}

//  出队操作
void QueuePop(LQueue* q, QNode* ret) {
	if (QueueEmpty(q)) {
		exit(0);
	}

	QNode* pHead = q->head->next;
	*ret = *pHead;
	q->head->next = pHead->next;
	if (pHead == q->tail) {
		q->tail = q->head;
	}
}

//  判断队空
int QueueEmpty(LQueue* q) {
	if (q->head == q->tail) {
		return 1;
	}

	return 0;
}

//  二叉树的层序遍历
void LevelOrder(BTNode* root) {
	LQueue q;
	InitQueue(&q);
	if (root) {
		QueuePush(&q, root);
	}

	while (!QueueEmpty(&q)) {
		QNode cur;
		QueuePop(&q, &cur);
		printf("%c ", (&cur)->val->val);

		if ((&cur)->val->left) {
			QueuePush(&q, (&cur)->val->left);
		}
		if ((&cur)->val->right) {
			QueuePush(&q, (&cur)->val->right);
		}
	}
}