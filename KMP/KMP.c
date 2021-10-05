#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char* chs;
	int length;
}SString;

void prefix_table(SString pattern, int prefix[], int n)
{
	prefix[0] = 0;
	int len = 0; // 前缀最后一个字符位置
	int i = 1;   // 后缀最后一个字符位置
	while (i < n)
	{
		if (pattern.chs[i] == pattern.chs[len])
		{
			len++;
			prefix[i] = len;
			i++;
		}
		else
		{
			if (len > 0)
			{
				len = prefix[len - 1];
			}
			else
			{
				prefix[i] = len;
				i++;
			}
		}
	}
}

void move_prefix(int prefix[], int n)
{
	int i = 0;
	for (i = n - 1; i > 0; i--)
	{
		prefix[i] = prefix[i - 1];
	}
	prefix[0] = -1;
}

void kmp_search(SString text, SString pattern) {
	int n = pattern.length;
	int* prefix = malloc(sizeof(int) * n);
	if (prefix == NULL) {
		printf("内存访问出错,已终止程序");
		exit(0);
	}
	prefix_table(pattern, prefix, n);
	move_prefix(prefix, n);
	
	// text[i]     len(text) = m;
	// pattern[j]  len(pattern) = l;
	int i = 0, j = 0;
	int m = text.length;
	int l = pattern.length;
	while (i < m)
	{
		if (j == l - 1 && text.chs[i] == pattern.chs[j]) {
			printf("Found Pattern at %d\n", i - j);
			j = prefix[j];
		}
		if (text.chs[i] == pattern.chs[j]) {
			i++; j++;
		}
		else {
			if (j >= 0 && j < l) {
				j = prefix[j];
				if (j == -1) { // 两个字符串的首字符失配时：1. i++是新的待匹配字符索引; 2. j++是回到pattern的首字符
					i++; j++;
				}
			}
		}
	}
}

int main()
{
	SString s1;
	s1.chs = "ABABCABAA";
	s1.length = 9;
	int prefix[9];

	SString s2;
	s2.chs = "AB";
	s2.length = 2;


	prefix_table(s1, prefix, 9);
	move_prefix(prefix, 9);
	kmp_search(s1, s2); // 0 2 5
	return 0;
}