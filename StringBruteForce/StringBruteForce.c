#define _CRT_SECURE_NO_WARNINGS 1
#define MAXLEN 132
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	char* chs; // 储存串的一维数组
	int length;       // 储存串的长度
}SString;

int StringBF(SString S, SString T, int pos); // 暴力搜索模式匹配（BF算法）
int main()
{
	SString S;
	S.chs ="chagjadjd\0";
	S.length = 9;

	SString T;
	T.chs = "agjk\0";
	T.length = 4;
	
	int pos = StringBF(S, T, 2);
	printf("%s中与%s相匹配的第一个位置是%d\n", S.chs, T.chs, pos);

	return 0;
}

int StringBF(SString S, SString T, int pos) // 暴力搜索模式匹配（BF算法）
{
	if (0 > pos || pos >= S.length)
	{
		printf("pos的范围不合法");
		return -1; // 返回错误索引-1
	}

	int i = pos, j = 0; //  i 和 j 表示当前主串S和模式串T中待比较字符的位置（0、1、2.......)
	while (i < S.length && j < T.length) // 两串(S、T)均未比较到串尾处
	{
		if (S.chs[i] == T.chs[j]) // 继续比较后继字符
		{
			i++;
			j++;
		}
		else  // 不相等则回溯到下次重新匹配的状态
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (i == S.length && j < T.length)
	{
		return -1;
	}
	else
	{
		return i - T.length;
	}
}