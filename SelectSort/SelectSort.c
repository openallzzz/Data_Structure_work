#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 对直接选择排序算法进行优化
void Optimize_SelectSort(int* nums, int numsSize) {
	int left = 0, right = numsSize - 1;

	while (left < right) {
		int min_i = left, max_i = right;
		for (int i = left; i <= right; i++) {
			if (nums[i] > nums[max_i])
				max_i = i;
			if (nums[i] < nums[min_i])
				min_i = i;
		}

		swap(&nums[left], &nums[min_i]);

		// 如果最小的换到了最左边的同时最大值也在最左边
		// 这个时候必须将max_i更新为min_i，这个位置存着最大的数
		// "left(max_i) <-> min_i" ---> "left(min) min_i(max)"
		// 这个时候要进行 max_i = min_i 才可以利用max_i访问到被换过来的最大值
		// 否则就是最小值
		if (max_i == left) {
			max_i = min_i;
		}
		swap(&nums[right], &nums[max_i]);
		++left;
		--right;
	}
}

void TestSelectSort() {
	int nums[10];
	FILE* pF;

	if ((pF = fopen("sortdatas.txt", "r")) == NULL) {
		printf("文件打开失败\n");
	}
	else {
		for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {
			fscanf(pF, "%d", &nums[i]);
		}
	}

	Optimize_SelectSort(nums, sizeof(nums) / sizeof(int));
	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {
		printf("%d ", nums[i]);
	}
}

int main() {
	TestSelectSort();
	return 0;
}