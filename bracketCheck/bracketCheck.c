#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

typedef char CheckBracketElem;
typedef struct
{
	CheckBracketElem* top;
	CheckBracketElem* base;
	int size;
}SqStack;

void SqStackInit(SqStack* s); // 初始化顺序栈
void SqStackPushBack(SqStack* s, CheckBracketElem x); // 顺序栈的入栈操作
void SqStackPopBack(SqStack* s, CheckBracketElem* retData); // 顺序栈的出栈操作
CheckBracketElem SqStackGetTop(SqStack* s); // 获得栈顶元素

int main()
{
	SqStack s;
	SqStackInit(&s);
	CheckBracketElem* Brackets = "((((()))))";
	CheckBracketElem CheckElem = 0;
	int braLen = strlen(Brackets);

	for (int i = 0; i < braLen; i++)
	{
		if (Brackets[i] == '(' || Brackets[i] == '[' || Brackets[i] == '{')
		{ // “左括号” 直接入栈
			SqStackPushBack(&s, Brackets[i]);
		}
		else
		{
			if ((&s)->top == (&s)->base)
			{
				printf("该括号表达式不匹配");
				return 0;
			}
			SqStackPopBack(&s, &CheckElem);
			if (Brackets[i] == ')')
			{
				if (CheckElem == '(')
				{
					continue;
				}
				else
				{
					printf("该括号表达式不匹配");
					return 0;
				}
			}
			if (Brackets[i] == ']')
			{
				if (CheckElem == '[')
				{
					continue;
				}
				else
				{
					printf("该括号表达式不匹配");
					return 0;
				}
			}
			if (Brackets[i] == '}')
			{
				if (CheckElem == '{')
				{
					continue;
				}
				else
				{
					printf("该括号表达式不匹配");
					return 0;
				}
			}
		}
	}
	if ((&s)->base == (&s)->top)
		printf("该括号表达式匹配");
	else
		printf("该括号表达式不匹配");
	return 0;
}

void SqStackInit(SqStack* s) // 初始化顺序栈
{
	s->base = (CheckBracketElem*)malloc(sizeof(CheckBracketElem) * 20);
	if (s->base == NULL)
	{
		printf("内存申请失败");
		exit(0);
	}

	s->top = s->base;
	s->size = 20;
}

void SqStackPushBack(SqStack* s, CheckBracketElem x) // 顺序栈的入栈操作
{
	if (s->top - s->base == s->size)
	{
		printf("栈空间已满，无法进行入栈操作");
		exit(0);
	}

	*(s->top) = x;
	s->top++;
}

void SqStackPopBack(SqStack* s, CheckBracketElem* retData) // 顺序栈的出栈操作
{
	if (s->base == s->top)
	{
		printf("栈空间为空，无法进行出栈");
		exit(0);
	}

	*retData = *(s->top - 1);
	s->top--;
}

CheckBracketElem SqStackGetTop(SqStack* s) // 获得栈顶元素
{
	if (s->base == s->top)
	{
		printf("栈为空，无法获取元素");
		exit(0);
	}

	return *(s->top - 1);
}