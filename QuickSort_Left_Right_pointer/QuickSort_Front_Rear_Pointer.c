#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 前后指针解决快排
void QuickSort(int* nums, int left, int right) {
	if (left >= right) {
		return;
	}

	int begin = left, end = right;
	int keyi = begin;

	while (begin < end) {
		// 右边找小
		while (begin < end && nums[end] >= nums[keyi]) {
			end--;
		}
		// 左边找大
		while (begin < end && nums[begin] <= nums[keyi]) {
			begin++;
		}

		swap(&nums[begin], &nums[end]);
	}

	swap(&nums[keyi], &nums[begin]);
	keyi = begin;

	QuickSort(nums, left, keyi - 1);
	QuickSort(nums, keyi + 1, right);
}

int main() {
	int nums[] = { 1, 5, 9, 7, 6, 8, 1, 3, 6, 5, 9, 7, 16};
	QuickSort(nums, 0, sizeof(nums) / sizeof(int) - 1);

	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) printf("%d ", nums[i]);
	return 0;
}