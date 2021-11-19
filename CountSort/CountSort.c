#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

// 适合数据比较集中的大量数据，对其值比较离散的数据不友好，不如其他高效的比较排序--快排、堆排、归并
void CountSort(int* nums, int n)
{
	int max = nums[0], min = nums[0];
	for (int i = 0; i < n; i++) {
		if (nums[i] > max)
		{
			max = nums[i];
		}
		if (nums[i] < min)
		{
			min = nums[i];
		}
	}


	int range = max - min + 1;

	// 辅助数组来统计每个数字出现的次数
	int* count = (int*)malloc(sizeof(int) * range);
	memset(count, 0, sizeof(int) * range);

	for (int i = 0; i < n; i++)
	{
		count[nums[i] - min]++;
	}
	int j = 0;
	for (int i = 0; i < range; i++) 
	{
		while (count[i]--)
		{
			nums[j++] = i + min;
		}
	}
	free(count);
}

int main()
{
	int nums[] = { 1, 5, 7, 9, 6, 3, 7, 6, 4, 1, 6, 7, 10, 4, 1, 6, 3, 7 };
	CountSort(nums, sizeof(nums) / sizeof(int));
	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) printf("%d ", nums[i]);
	return 0;
}