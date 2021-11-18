#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include "LinkStack.h"

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void QuickSort(int* nums, int left, int right)
{
	LinkStackNode* s = NULL;
	LinkstackInit(&s);
	LinkStackPushFront(&s, right);
	LinkStackPushFront(&s, left);
	while (s)
	{
		int left = 0, right = 0;
		LinkStackGetTopElem(s, &left);
		LinkStackPopFront(&s);
		LinkStackGetTopElem(s, &right);
		LinkStackPopFront(&s);

		// 挖坑法
		int begin = left, end = right;
		int key = nums[begin];
		int pivot = begin;
		while (begin < end)
		{
			while (begin < end && nums[end] >= key)
			{
				end--;
			}
			swap(&nums[pivot], &nums[end]);
			pivot = end;
			while (begin < end && nums[begin] <= key)
			{
				begin++;
			}
			swap(&nums[begin], &nums[pivot]);
			pivot = begin;
		}
		pivot = begin;
		nums[pivot] = key;

		// [ left  pivot -1 ] pivot  [ pivot + 1  right ]
		// 将待排序的子数组记录在栈中，模拟递归
		if (right > pivot + 1) // 相当于递归的终止条件
		{
			LinkStackPushFront(&s, right);
			LinkStackPushFront(&s, pivot + 1);
		}
		
		if (pivot - 1 > left) // 相当于递归的终止条件
		{
			LinkStackPushFront(&s, pivot - 1);
			LinkStackPushFront(&s, left);
		}
	}
}

int main()
{
	int nums[] = { 1, 6, 7, 2, 9, 8, 4, 3, 7, 11, 54, 0, 74};
	QuickSort(nums, 0, sizeof(nums) / sizeof(int) - 1);
	for (int i = 0; i < sizeof(nums) / sizeof(int); i++)
	{
		printf("%d ", nums[i]);
	}
	return 0;
}