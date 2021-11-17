#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 在对数据进行快速排序的时候
// 如果数据是有序或者接近有序的话
// 快排的效率会变的很差
// 我们借助三数取中来解决这个问题哈
int getMidIndex(int* nums, int left, int right) {
	if (left >= right) return -1;

	int mid = (left + right) >> 1;

	if (nums[left] > nums[mid]) // mid left
	{
		if (nums[mid] < nums[right])         // mid right left
		{       
			return right;
		}
		else if (nums[left] > nums[right])   // right mid left
		{  
			return mid;
		}
		else {                               // mid left right
			return left;
		}
	}
	else                        // left mid
	{ 
		if (nums[mid] > nums[right])        // left right mid 
		{
			return right;
		}
		else if (nums[left] > nums[right])  // right left mid 
		{
			return left;
		}
		else                                // left mid right 
		{
			return mid;
		}
	}
}

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

void QuickSort(int* nums, int left, int right) {
	// 借助[1, 2]来理解这个return 
	if (left >= right)
		return;
	// left 和 right 就是整个数组的索引区间，因为需要递归解决问题
	// 所以需要保存left和right，我们另设begin和end来保存整个数组的索引区间

	// 使得最左边的值始终为中间值
	int index = getMidIndex(nums, left, right);
	swap(&nums[left], &nums[index]);

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

	// 进行快排时，最后要被处理的数据比较少如果依然递归调用的话会增加不必要的栈帧消耗
	// 于是我们对小区间排序使用其他排序来优化快排

	// 优化前
	//QuickSort(nums, left, pivot - 1);
	//QuickSort(nums, pivot + 1, right);

	// 优化后-----针对小区间的优化
	if (pivot - 1 - left + 1 > 10)
	{
		QuickSort(nums, left, pivot - 1);
	}
	else
	{
		InsertSort(nums + left, pivot - 1 - left + 1);
	}

	if (right - (pivot + 1) + 1 > 10)
	{
		QuickSort(nums, pivot + 1, right);
	}
	else
	{
		InsertSort(nums + pivot + 1, right - (pivot + 1) + 1);
	}
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