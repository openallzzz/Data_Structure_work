#define _CRT_SECURE_NO_WARNINGS 1
#include "LinkStack.h"

void LinkstackInit(LinkStackNode** phead) // 链式栈的初始化
{
	*phead = NULL;
}

LinkStackNode* BuyNewLinkStackNode(LinkStackDataType val) // 创建一个链式栈的结点 并返回其地址
{
	LinkStackNode* newNode = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	if (newNode == NULL)
	{
		printf("申请内存失败");
		exit(0);
	}
	newNode->data = val;
	newNode->next = NULL;
	return newNode;
}

void LinkStackPushFront(LinkStackNode** pphead, int val) // 链式栈的压栈操作
{
	LinkStackNode* newNode = BuyNewLinkStackNode(val);
	if (*pphead == NULL)
	{
		*pphead = newNode;
	}
	else
	{
		//单链表头插即为链式栈的压栈
		newNode->next = *pphead;
		*pphead = newNode;
	}
}

void LinkStackPopFront(LinkStackNode** pphead)  // 链式栈的出栈操作
{
	if (*pphead == NULL)
	{
		printf("栈中无数据，无法出栈\n");
		exit(0);
	}

	LinkStackNode* nextNode = (*pphead)->next;
	//单链表的头删即为链式栈的出栈操作
	free(*pphead);
	*pphead = nextNode;
}

void LinkStackGetTopElem(LinkStackNode* phead, LinkStackDataType* retData)  // 获取链式栈的栈顶元素
{
	if (phead == NULL)
	{
		printf("栈中无数据，无法返回元素\n");
		return;
	}
	else
	{
		*retData = phead->data;
	}
}

void LinkStackPrint(LinkStackNode* phead)  // 打印栈中的数据
{
	if (phead == NULL)
	{
		printf("栈空间中没有数据\n");
	}
	else
	{
		printf("栈顶:->");
		while (phead != NULL)
		{
			printf("%d ", phead->data);
			phead = phead->next;
			if(phead == NULL)
				printf("<-栈底\n");
		}
	}
}

void LinkStackClear(LinkStackNode** pphead) // 清空栈中的数据
{
	LinkStackNode* delete_tmp = NULL;
	while (*pphead)
	{
		delete_tmp = *pphead;
		(*pphead) = (*pphead)->next;
		free(delete_tmp);
	}
	*pphead = NULL;
}