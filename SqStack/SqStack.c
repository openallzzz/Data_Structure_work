#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

#define MAX_SZIE_SqStack 8  //定义顺序栈的最大容量
typedef int SqStackDataType;
typedef struct
{
	SqStackDataType* top; //顺序栈的栈顶
	SqStackDataType* base;//顺序栈的栈底
	int SqStackSize;      //记录顺序栈的容量
}SqStack;         //Sequence Stack —— 顺序栈

void SqStackInit(SqStack* s);                                    // 顺序栈的初始化
void SqStackPushBack(SqStack* s, SqStackDataType x);             // 顺序栈的入栈操作
void SqStackPopBack(SqStack* s, SqStackDataType* retTopElem);    // 顺序栈的出栈操作
void SqStackGetTopElem(SqStack* s, SqStackDataType* retTopElem); // 获取顺序栈的栈顶元素
void SqStackPrint(SqStack* s);                                   // 打印栈元素
int main()
{
	SqStack s;
	SqStackInit(&s);
	SqStackPushBack(&s, 5);
	SqStackPushBack(&s, 2);
	SqStackPushBack(&s, 9);
	SqStackPushBack(&s, 4);
	SqStackPushBack(&s, 1);
	SqStackPrint(&s);
	int top0;
	SqStackGetTopElem(&s, &top0);
	printf("top:%d\n", top0);
	int top1;
	SqStackPopBack(&s, &top1);
	printf("出栈元素:%d\n", top1);
	SqStackPrint(&s);
	SqStackPushBack(&s, 0);
	SqStackPrint(&s);
	SqStackPopBack(&s, &top1);
	printf("出栈元素:%d\n", top1);
	SqStackPopBack(&s, &top1);
	printf("出栈元素:%d\n", top1);
	SqStackPopBack(&s, &top1);
	printf("出栈元素:%d\n", top1);
	SqStackPopBack(&s, &top1);
	printf("出栈元素:%d\n", top1);
	SqStackPopBack(&s, &top1);
	printf("出栈元素:%d\n", top1);

	SqStackPushBack(&s, 56);
	SqStackPushBack(&s, 67);
	SqStackPushBack(&s, 75);
	SqStackPrint(&s);
	return 0;
}


void SqStackInit(SqStack* s)
{
	s->base = (SqStackDataType*)malloc(MAX_SZIE_SqStack * sizeof(SqStackDataType));
	if (s->base == NULL)
	{
		printf("申请内存失败");
		exit(0);
	}

	s->top = s->base; //初始化后栈中没有元素
	s->SqStackSize = MAX_SZIE_SqStack;
}
void SqStackPushBack(SqStack* s, SqStackDataType x)
{
	if (s->top - s->base == s->SqStackSize)  // 栈空间已满
	{
		printf("栈空间已满");
		exit(0);
	}

	*(s->top++) = x;// 先取出栈顶指针 再解引用 最后赋值
}
void SqStackPopBack(SqStack* s, SqStackDataType* retTopElem)
{
	if (s->top == s->base)  //栈为空
	{
		printf("栈为空，无法出栈");
		exit(0);
	}

	*retTopElem = *(s->top-1);
	s->top--;
	if (s->top == s->base)
	{
		printf("(%d已为栈中最后一个元素)\n",*retTopElem);
	}
}
void SqStackGetTopElem(SqStack* s, SqStackDataType* retTopElem)
{
	if (s->base == s->top)
	{
		printf("栈为空，无法获取栈顶元素");
		exit(0);
	}

	*retTopElem = *(s->top-1);
}
void SqStackPrint(SqStack* s)
{
	if (s->base == s->top)
	{
		printf("栈为空，没有元素可打印");
		exit(0);
	}
	SqStackDataType* base_tmp = s->base;
	printf("栈底-> ");
	while (base_tmp != s->top)
	{
		printf("%d ", *base_tmp);
		base_tmp++;
	}
	printf("<-栈顶\n");
}