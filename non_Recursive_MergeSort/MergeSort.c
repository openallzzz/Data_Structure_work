#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

// 非递归时一定需要修正区间值
void MergeSortNonR(int* nums, int n)
{
	// 分配一个辅助数组，来存放每次归并的结果
	int* tmp = (int*)malloc(sizeof(int) * n);

	int gap = 1; // 初始时归并的每组数据的个数
	while (gap < n)
	{
		// 分成[i,  i + gap - 1]  [i + gap, i + 2 * gap - 1]
		for (int i = 0; i < n; i += 2 * gap)
		{
			// 获取两个需要归并的数组区间
			int begin1 = i, end1 = i + gap - 1;
			int begin2 = i + gap, end2 = i + 2 * gap - 1;

			// 归并过程中右区间可能不存在，进行修正
			if (begin2 >= n)
			{
				break;
			}

			// 归并过程中右半区间算多了，进行修正
			if (end2 >= n)
			{
				end2 = n - 1;
			}

			int index = i;
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

			// 合并
			while (begin1 <= end1)
			{
				tmp[index++] = nums[begin1++];
			}
			while (begin2 <= end2)
			{
				tmp[index++] = nums[begin2++];
			}
			// 合并结束

			// 拷贝回去
			for (int j = i; j <= end2; j++)
			{
				nums[j] = tmp[j];
			}
		}

		gap *= 2;
		// 1 2 3 4 5 6 7 8 9 -- gap = 1
		// 12   34   56   78 -- gap = 2
		// 1 2 3 4   5 6 7 8 -- gap = 4
	}
	free(tmp);
}
int main()
{
	int nums[] = { 1, 5, 9, 6, 3, 0, 7, 9, 10, 11, 20, 2 };

	MergeSortNonR(nums, sizeof(nums) / sizeof(int));
	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) printf("%d ", nums[i]);
	return 0;
}