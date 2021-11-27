#define _CRT_SECURE_NO_WARNINGS 1
#define pages 1000

/*
* 创建一本书的页数的索引表 [1, 1000]
*/
#include <stdio.h>
#include <assert.h>

// 索引表
typedef struct
{
	int maxValue; // 所选块中的最大关键字
	int left;     // 块所在的区间的左端点
	int right;    // 块所在的区间的右端点
}IndexTable;


// 只是为了测试分块查找。一般索引表不需要自己写
IndexTable* InitIndexTable()
{
	//  开辟大小为4的索引表的数组空间
	IndexTable* res = (IndexTable*)malloc(sizeof(IndexTable) * 4);

	// 建立索引信息，默认索引表按关键字是严格升序的
	for (int i = 0; i < 4; i++) {
		res[i].maxValue = 250 * (i + 1);
		res[i].left  = i * 250;
		res[i].right = 250 * (i + 1) - 1;
	}

	return res;
}

int BlockingSearch(int* nums, IndexTable* table, int tableSize, int targetVal)
{
	// 1. 先查找块
	int begin = 0, end = tableSize - 1;
	int mid = (begin + end) / 2;
	
	int targetBlock = 0;
	// 对于二分法找块，边界情况分两种，需要特判
	// 1. begie越界；2. end越界。
	while (begin <= end)
	{
		if (table[mid].maxValue < targetVal)
		{
			begin = mid + 1;
		}
		else if (table[mid].maxValue > targetVal)
		{
			end = mid - 1;
		}
		else
		{
			targetBlock = mid;
			break;
		}

		mid = (begin + end) / 2;
	}
	// 
	if (begin > end)
	{
		// 一般情况，我们必然是在begin块中查找目标值
		targetBlock = begin;
		// begin越界
		// targetVal超过了索引表中所有的关键值，这是必然找不到的。
		if (begin > tableSize - 1) return -1; 
		// end越界
		// tagetgetVal虽然小于所有的关键值，但是不能确保必然找不到，因为关键值存的是每个子区间的最大值。
		if (end < 0) targetBlock = begin;
	}

	// 2. 由于块内的元素是无序的，我们在块内进行顺序查找
	for (int i = table[targetBlock].left; i < table[targetBlock].right; i++)
	{
		if (nums[i] == targetVal) return i;
	}

	return -1;
}

int main()
{
	int index[pages];
	int val = 0;
	FILE* pF = NULL;
	assert(pF = fopen("pagesRandom.txt", "r"));

	for (int i = 0; i < pages; i++) assert(fscanf(pF, "%d", &index[i]));
	IndexTable* table = InitIndexTable();
	printf("请输入你需要查找的关键字的值：");
	assert(scanf("%d", &val));
	int res = BlockingSearch(index, table, 4, val);


	// if(res) 这段语句不能这么写，在C语言中0为假，非0为真，所以对于负数来说，其也为真
	if (res >= 0)
	{
		printf("%d在原数据中的索引是：%d\n", val, res);
	}
	else
	{
		printf("原数组中无目标值%d\n", val);
	}
	return 0;
}