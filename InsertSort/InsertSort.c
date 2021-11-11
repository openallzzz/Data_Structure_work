#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

// ≤Â»Î≈≈–Ú
void InsertSort(int* nums, int numsSize) {
	for (int i = 0; i < numsSize - 1; i++) {
		int end = i;
		int tmp = nums[end + 1];
		while (end >= 0) {
			if (nums[end] > tmp) {
				nums[end + 1] = nums[end];
				end--;
			}
			else break;
		}
		nums[end + 1] = tmp;
	}
}

void TestInsertSort() {
	int nums[] = { 1, 5, 7, -6, 3, 2, -1, 0, 4, 9 };
	InsertSort(nums, sizeof(nums) / sizeof(int));
	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {
		printf("%d ", nums[i]);
	}
	printf("\n");
}

int main() {
	TestInsertSort();
	return 0;
}