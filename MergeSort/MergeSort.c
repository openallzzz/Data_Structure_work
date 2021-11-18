#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

void _MergeSort(int* nums, int left, int right, int* tmp)
{
	if (left >= right)
	{
		return;
	}

	int mid = (left + right) >> 1;
	// 使得 [left mid] & [mid + 1, right] 这两部分有序
	_MergeSort(nums, left, mid, tmp);
	_MergeSort(nums, mid + 1, right, tmp);

	// 有序之后开始合并
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = left;
	while (begin1 <= end1 && begin2 <= end2)
	{
		if (nums[begin1] < nums[begin2])
		{
			tmp[index++] = nums[begin1++];
		}
		else 
		{
			tmp[index++] = nums[begin2++];
		}
	}

	while (begin1 <= end1)
	{
		tmp[index++] = nums[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = nums[begin2++];
	}

	// 合并之后返回有序的部分
	for (int i = left; i <= right; i++)
	{
		nums[i] = tmp[i];
	}
}

void MergeSort(int* nums, int n) 
{
	int* tmp = (int*)malloc(sizeof(int) * n);
	_MergeSort(nums, 0, n - 1, tmp);
	free(tmp);
}

int main() {
	int nums[] = { 2, 3, 7, 258, 0, 4, 5, 6, 6 ,7, 75, 58, 8, 8, 1 };
	MergeSort(nums, sizeof(nums) / sizeof(int));
	for (int i = 0; i < sizeof(nums) / sizeof(int); i++)
	{
		printf("%d ", nums[i]);
	}
	return 0;
}