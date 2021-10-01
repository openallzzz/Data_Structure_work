#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 10

typedef int SqStackData;
typedef struct
{
	SqStackData* top;
	SqStackData* base;
	int Size;
}SqStack;

void SqStackInit(SqStack* s); //  顺序栈的初始化
void SqStackPushBack(SqStack* s, SqStackData x); // 顺序栈的压栈
void SqStackPopBack(SqStack* s, SqStackData* retData); // 顺序栈的出栈

int main()
{
	SqStack s;
	SqStackInit(&s);

	int reception_Num = 0, remainDer = 0, tmp_Num = 0;
	scanf("%d", &reception_Num);
	tmp_Num = reception_Num;
	while (reception_Num)
	{
		remainDer = reception_Num % 8;
		SqStackPushBack(&s, remainDer); // 对每一次取余的的结果压入栈中
		reception_Num /= 8;
	}
	printf("%d的八进制为：", tmp_Num);
	while ((&s)->top != (&s)->base)
	{
		SqStackData ret = 0;
		SqStackPopBack(&s, &ret);
		printf("%d", ret);
	}

	return 0;
}


void SqStackInit(SqStack* s)
{
	s->base = (SqStackData*)malloc(sizeof(SqStack) * MAX_STACK_SIZE);
	if (s->base == NULL)
	{
		printf("申请内存失败");
		exit(0);
	}
	s->top = s->base; // 初始化后栈中无数据 为空栈状态
	s->Size = 0;
}


void SqStackPushBack(SqStack* s, SqStackData x)
{
	if (s->top - s->base == MAX_STACK_SIZE) // 栈已满
		exit(0);

	*(s->top) = x;
	s->top++;
	s->Size++;
}

void SqStackPopBack(SqStack* s, SqStackData* retData)
{
	if (s->top == s->base) // 空栈状态无数据可出栈
		exit(0);

	*retData = *(s->top-1);
	s->top--;
	s->Size--;
}