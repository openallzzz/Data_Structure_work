#define _CRT_SECURE_NO_WARNINGS 1
#define MAXSIZE 500

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int numsSeq[MAXSIZE];
	int headIndex, tailIndex;
}SqQueue;

void SqQueueInit(SqQueue* s); // 初始化
void SqQueuePushBack(SqQueue* s, int num); // 入队列
void SqQueuePopFront(SqQueue* s, int* retQueueTopNum); // 出队列
void SqQueueViewTop(SqQueue* s, int* queueTopNum); // 查看队头元素

void PrintYangTriang(int Row); // 打印杨辉三角的前Row行


int main()
{
	PrintYangTriang(4);
	return 0;
}



void SqQueueInit(SqQueue* s) {
	if (s == NULL) {
		printf("nullptr error!");
		exit(0);
	}

	s->headIndex = 0;
	s->tailIndex = 0;
}
void SqQueuePushBack(SqQueue* s, int num) {
	if (s->tailIndex == MAXSIZE - 1) {
		printf("segfault!");
		exit(0);
	}

	s->numsSeq[s->tailIndex] = num;
	s->tailIndex++;
}
void SqQueuePopFront(SqQueue* s, int* retQueueTopNum) {
	if (s->tailIndex == s->headIndex) {
		printf("Queue FakaOverflow!");
		exit(0);
	}

	*retQueueTopNum = s->numsSeq[s->headIndex];
	s->headIndex++;
}

void SqQueueViewTop(SqQueue* s, int* queueTopNum) {
	if (s->tailIndex == s->headIndex) {
		printf("Queue FakeOverflow!");
		exit(0);
	}

	*queueTopNum = s->numsSeq[s->headIndex];
}

void PrintYangTriang(int Row) {
	if (Row <= 0) {
		printf("parameter illegal");
		exit(0);
	}

	// 打印第一行
	for (int i = 0; i < Row; i++) {
		printf("   ");
	}
	printf("%d\n", 1);

	// 从第二行开始打印
	SqQueue numsseq;
	SqQueueInit(&numsseq);
	SqQueuePushBack(&numsseq, 0);
	SqQueuePushBack(&numsseq, 1);
	SqQueuePushBack(&numsseq, 1);

	int rowLog = 1;
	int retQueueTopNum = 0, queueTopNum = 0;
	while (rowLog < Row) {
		for (int i = 0; i < Row - rowLog; i++) {
			printf("   ");
		}
		SqQueuePushBack(&numsseq, 0);
		
		do {
			SqQueuePopFront(&numsseq, &retQueueTopNum);
			SqQueueViewTop(&numsseq, &queueTopNum);

			if (queueTopNum != 0) {
				printf("%-6d", queueTopNum);
			}
			SqQueuePushBack(&numsseq, queueTopNum + retQueueTopNum);
		} while (queueTopNum != 0);
		rowLog++;
		printf("\n");
	}
	while (numsseq.headIndex != numsseq.tailIndex) {
		SqQueuePopFront(&numsseq, &retQueueTopNum);
		if (retQueueTopNum != 0) {
			printf("%-6d", retQueueTopNum);
		}
	}
}