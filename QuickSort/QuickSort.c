#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

void QuickSort(int* nums, int left, int right) {
	// 借助[1, 2]来理解这个return 
	if (left >= right)
		return;
	// left 和 right 就是整个数组的索引区间，因为需要递归解决问题
	// 所以需要保存left和right，我们另设begin和end来保存整个数组的索引区间

	int begin = left, end = right;
	int key = nums[left]; // 每一次取最左边的值为key
	int pivot = left; // 坑位留给被保存的值

	while (begin < end) {
		// 右边找小，放到左边
		while (begin < end && nums[end] >= key) {
			end--;
		}// 出来的是 nums[right] < key ---- 放到左边
		
		nums[pivot] = nums[end];
		pivot = end;
		// 左边找大，放到右边
		while (begin < end && nums[begin] <= key) {
			begin++;
		}// 出来的是 nums[left] > key ---- 放到右边
		nums[pivot] = nums[begin];
		pivot = begin;
	}
	// 此时 left == right 任选一个赋值即可
	pivot = begin;
	nums[pivot] = key;

	// 此时 [left, right] 被分成 [left, pivot - 1] pivot [pivot + 1, right]
	// 递归调用QuickSort即可
	QuickSort(nums, left, pivot - 1);
	QuickSort(nums, pivot + 1, right);
}

void TestQuickSort() {
	int nums[10];
	FILE* pF;
	if ((pF = fopen("sortdatas.txt", "r")) == NULL) {
		printf("文件打开失败\n");
		exit(0);
	}
	else {
		for (int i = 0; i < 10; i++) {
			fscanf(pF, "%d", &nums[i]);
		}
	}

	QuickSort(nums, 0, sizeof(nums) / sizeof(int) - 1);
	for (int i = 0; i < 10; i++) {
		printf("%d ", nums[i]);
	}
}
int main() {
	TestQuickSort();
	return 0;
}