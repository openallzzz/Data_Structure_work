#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// 满足前提才可以使用向下调整算法（调整为大堆
// 根结点的左右子树为堆（大堆和小堆
void AdjustDown(int* nums, int numsSize, int rootIndex) {
	int parent = rootIndex;
	int child = 2 * parent + 1; // 默认为左孩子

	while (child < numsSize) {
		// 右孩子大于左孩子，选择右孩子
		if (child + 1 < numsSize && nums[child + 1] > nums[child]) {
			child += 1;
		}

		// 进行调整
		if (nums[parent] < nums[child]) {
			Swap(&nums[parent], &nums[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}


// 大堆升序 
// 小堆降序
void HeapSort(int* nums, int numsSize) {
	// 从最后一个非叶子结点开始从下往上建堆
	for (int i = (numsSize - 2) / 2; i >= 0; i--) {
		AdjustDown(nums, numsSize, i);
	}

	// 升序创建大堆，因为每一次将未排序的数据的最大值移到数组最后一个，
	// 接下来除去已经做交换的数据，其他数据就只是需要做向下调整重新转
	// 换为大堆
	int end = numsSize - 1;
	while (end > 0) {
		// 将最大值移到后面
		Swap(&nums[0], &nums[end]);
		// 对交换后的数组除去已经移到数组后面的数据进行向下调整
		AdjustDown(nums, end, 0);
		end--;
	}
}

void TestHeapSort() {
	int nums[10];
	FILE* pF;
	if ((pF = fopen("sortdatas.txt", "r")) == NULL) {
		printf("文件打开失败！");
		exit(0);
	}

	for (int i = 0; i < 10; i++) {
		fscanf(pF, "%d", &nums[i]);
	}

	HeapSort(nums, sizeof(nums) / sizeof(int));
	for (int i = 0; i < sizeof(nums) / sizeof(int); i++) {
		printf("%d ", nums[i]);
	}
}

int main() {
	TestHeapSort();
	return 0;
}