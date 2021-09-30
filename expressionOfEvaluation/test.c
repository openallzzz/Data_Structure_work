#define _CRT_SECURE_NO_WARNINGS 1
#define MAX_SQSTACK_SIZE 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char SqStackData;
typedef int SqStackDataOperNum;
typedef struct
{
	SqStackData* top;
	SqStackData* base;
	int MaxSqStackCapacity;
}SqStack; // 字符型栈 - 存放运算符
typedef struct
{
	SqStackDataOperNum* top;
	SqStackDataOperNum* base;
	int MaxNumSize;
}SqOperNumStack; // 整型栈 - 存放操作数


void SqStackInit(SqStack* s); // 顺序栈的初始化
void SqStackPushBack(SqStack* s, SqStackData x); // 顺序栈的入栈
void SqStackPopBack(SqStack* s, SqStackData* retData); // 顺序栈的出栈
SqStackData SqStackGetTop(SqStack* s); // 获取栈顶元素
void SqStackRemovetop(SqStack* s); // 删除栈顶元素

void SqOperNumStackInit(SqOperNumStack* s); // 初始化
void SqOperNumStackPushBack(SqOperNumStack* s, SqStackDataOperNum x); // 顺序栈的入栈
void SqOperNumStackPopBack(SqOperNumStack* s, SqStackDataOperNum* retData); // 顺序栈的出栈
void SqOperNumStackRemovetop(SqOperNumStack* s); // 删除栈顶元素

char assertPriority(SqStackData operator0, SqStackData operator1); // 判断两个操作符的优先级
SqStackDataOperNum fourOperations(SqStackDataOperNum a, SqStackData operator, SqStackDataOperNum b); // 二元操作符的运算

int main()
{
	SqStack s;
	SqStackData res = 0;
	
	SqStackInit(&s);
	// 入栈操作
	SqStackPushBack(&s, 'h');
	SqStackPushBack(&s, 'p');
	SqStackPushBack(&s, 't');
	SqStackPushBack(&s, 'e');
	SqStackPushBack(&s, 'l');
	SqStackPushBack(&s, 'b');
	// 删除栈顶元素
	SqStackRemovetop(&s);
	SqStackRemovetop(&s);
	while ((&s)->top != (&s)->base)
	{
		SqStackPopBack(&s, &res);
		printf("%c ", res);
	}
	printf("\n");
	// 以上对栈的测试成功 
	
	// 接下来解决表达式求值的算法
	SqStackData str[] = "(7*5)+9*3-2/2"; // (7*5) + 9 * 3 - 2 = 61
	int strLen = strlen(str), i = 0;

	SqOperNumStack OperNum; // 存放操作数的栈
	SqStack Operator; // 存放操作符的栈
	
	//初始化栈
	SqOperNumStackInit(&OperNum);
	SqStackInit(&Operator);

	while(i < strLen)
	{
		SqStackData oper = 0;
		SqStackDataOperNum top = 0, afterTop = 0;
		
		if (str[i] != '*' && str[i] != '/' && str[i] != '+' && str[i] != '-' && str[i] != '(' && str[i] != ')')
		{
			SqStackDataOperNum num = (int)(str[i] - '0');
			SqOperNumStackPushBack(&OperNum, num);
			i++;
		}
		else  // 读到了操作符
		{
			if ((&Operator)->base == (&Operator)->top) // 存放操作符的栈为空时，直接将读入的操作符入栈
			{
				SqStackPushBack(&Operator, str[i]); // str[i] 为操作符
				i++;
			}
			else // 操作符栈中有运算符
			{
				switch (assertPriority(SqStackGetTop(&Operator), str[i]))
				{
				case '<':  // 遍历过程中遇到的操作符优先级高于栈顶的操作符时,直接将其入栈
					SqStackPushBack(&Operator, str[i]);
					i++;
					break;							    
				case '>':  // 相反则弹出栈顶的运算符做相应的运算，再将运算结果压入OperNum栈中
					SqStackPopBack(&Operator, &oper); // oper 为接下来要进行运算的运算符
					SqOperNumStackPopBack(&OperNum, &top);
					SqOperNumStackPopBack(&OperNum, &afterTop);
					SqOperNumStackPushBack(&OperNum, fourOperations(top, oper, afterTop));
					break;
				case '=':
					SqStackRemovetop(&Operator);
					i++;
					break;
				}
			}
		}

		if (i == strLen)
		{
			while (Operator.base != Operator.top)
			{
				SqStackPopBack(&Operator, &oper); // oper 为接下来要进行运算的运算符
				SqOperNumStackPopBack(&OperNum, &top);
				SqOperNumStackPopBack(&OperNum, &afterTop);
				SqOperNumStackPushBack(&OperNum, fourOperations(afterTop, oper, top));
			}
		}
	}
	int result = 0;
	if (Operator.base == Operator.top)
		printf("%d", *(OperNum.top-1));
	else
	{
		result = fourOperations(*(OperNum.top - 2), *(Operator.top - 1), *(OperNum.top - 1));
		printf("%d", result);
	}
	
	return 0;
}

void SqStackInit(SqStack* s)
{
	s->base = (SqStackData*)malloc(sizeof(SqStackData) * MAX_SQSTACK_SIZE);
	if (s->base == NULL)
		exit(0);

	//申请内存成功 初始化栈的空间
	s->top = s->base;
	s->MaxSqStackCapacity = MAX_SQSTACK_SIZE;
}

void SqStackPushBack(SqStack* s, SqStackData x)
{
	if (s->top - s->base == s->MaxSqStackCapacity)
		exit(0);

	//可进行入栈操作
	*(s->top) = x;
	s->top++;
}

void SqStackPopBack(SqStack* s, SqStackData* retData)
{
	if (s->base == s->top)
		exit(0);

	// 可进行出栈操作
	*retData = *(s->top - 1);
	s->top--;
}
SqStackData SqStackGetTop(SqStack* s) // 获取操作符栈中的栈顶元素
{
	if(s->base != s->top)
		return *(s->top - 1);
}

void SqStackRemovetop(SqStack* s)
{
	if (s->base == s->top)
		exit(0);

	// 可进行出栈操作
	s->top--;
}

void SqOperNumStackInit(SqOperNumStack* s) // 初始化
{
	s->base = (SqStackDataOperNum*)malloc(sizeof(SqStackDataOperNum) * MAX_SQSTACK_SIZE);
	if (s->base == NULL)
		exit(0);

	s->top = s->base;
	s->MaxNumSize = MAX_SQSTACK_SIZE;
}
void SqOperNumStackPushBack(SqOperNumStack* s, SqStackDataOperNum x) // 顺序栈的入栈
{
	if (s->top - s->base == s->MaxNumSize)
		exit(0);

	*(s->top) = x;
	s->top++;
}
void SqOperNumStackPopBack(SqOperNumStack* s, SqStackDataOperNum* retData) // 顺序栈的出栈
{
	if (s->base == s->top)
		exit(0);

	*retData = *(s->top - 1);
	s->top--;
}
void SqOperNumStackRemovetop(SqOperNumStack* s) // 删除栈顶元素
{
	if (s->base == s->top)
		exit(0);

	s->top--;
}

char assertPriority(SqStackData operator0, SqStackData operator1) // 判断运算符之间的优先级
{
	if (operator0 == '+' || operator0 == '-')
	{
		if (operator1 == '+' || operator1 == '-' || operator1 == ')')
			return '>';
		else
			return '<';
	}
	else if (operator0 == '*' || operator0 == "/")
	{
		if (operator1 == '+' || operator1 == '-' || operator1 == ')' || operator1 == '/' || operator1 == '*')
			return '>';
		else
			return '<';
	}
	else if (operator0 == '(')
	{
		if (operator1 == ')')
			return '=';
		else
			return '<';
	}
	else
		return '>';
}

SqStackDataOperNum fourOperations(SqStackDataOperNum a, SqStackData operator, SqStackDataOperNum b)
{
	if (operator == '+')
		return a + b;
	if (operator == '-')
		return a - b;
	if (operator == '*')
		return a * b;
	if (operator == '/')
		return a / b;
}
