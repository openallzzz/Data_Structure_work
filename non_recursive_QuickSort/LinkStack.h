#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef int LinkStackDataType;
typedef struct LinkStackNode
{
	LinkStackDataType data;
	struct LinkStackNode* next;
}LinkStackNode;

void LinkstackInit(LinkStackNode** phead); // 链式栈的初始化
LinkStackNode* BuyNewLinkStackNode(LinkStackDataType val); // 创建一个链式栈的结点 并返回其地址
void LinkStackPushFront(LinkStackNode** pphead, int val); // 链式栈的压栈操作
void LinkStackPopFront(LinkStackNode** pphead);  // 链式栈的出栈操作
void LinkStackGetTopElem(LinkStackNode* phead, LinkStackDataType* retData);  // 获取链式栈的栈顶元素
void LinkStackPrint(LinkStackNode* phead);  // 打印栈中的数据
void LinkStackClear(LinkStackNode** pphead); // 清空栈中的数据
