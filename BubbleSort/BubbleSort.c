#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>


void BubbleSort(int* nums, int numsSize) {
	for (int i = 0; i < numsSize - 1; i++) {
		int flag = 1;
		for (int j = 0; j < numsSize - i - 1; j++) {
			if (nums[j] > nums[j + 1]) {
				int tmp = nums[j];
				nums[j] = nums[j + 1];
				nums[j + 1] = tmp;
				flag = 0;
			}
		}
		if (flag) break;
	}
}

void TestBubbleSort() {
	int nums[] = { 1, 5, 7, -6, 3, 2, -1, 0, 4, 9 };
	BubbleSort(nums, sizeof(nums) / sizeof(int));

	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}
int main() {
	TestBubbleSort();
	return 0;
}