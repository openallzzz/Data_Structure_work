#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

typedef char BTDataType;

typedef struct BinaryTreeNode
{
	struct BinaryTreeNode* LeftNode;
	struct BinaryTreeNode* RightNode;
	BTDataType val;
}BTNode;

void PrevOrder(BTNode* root) {
	if (root == NULL) {
		printf("NULL ");
		return;
	}

	printf("%c ", root->val);
	PrevOrder(root->LeftNode);
	PrevOrder(root->RightNode);
}

void InOrder(BTNode* root) {
	if (root == NULL) {
		printf("NULL ");
		return;
	}
	InOrder(root->LeftNode);
	printf("%c ", root->val);
	InOrder(root->RightNode);

}

void PostOrder(BTNode* root) {
	if (root == NULL) {
		printf("NULL ");
		return;
	}
	PostOrder(root->LeftNode);
	PostOrder(root->RightNode);
	printf("%c ", root->val);
}
int main()
{
	BTNode* A = (BTNode*)malloc(sizeof(BTNode));
	A->LeftNode = NULL;
	A->RightNode = NULL;
	A->val = 'A';
	
	BTNode* B = (BTNode*)malloc(sizeof(BTNode));
	B->LeftNode = NULL;
	B->RightNode = NULL;
	B->val = 'B';

	BTNode* C = (BTNode*)malloc(sizeof(BTNode));
	C->LeftNode = NULL;
	C->RightNode = NULL;
	C->val = 'C';

	BTNode* D = (BTNode*)malloc(sizeof(BTNode));
	D->LeftNode = NULL;
	D->RightNode = NULL;
	D->val = 'D';

	BTNode* E = (BTNode*)malloc(sizeof(BTNode));
	E->LeftNode = NULL;
	E->RightNode = NULL;
	E->val = 'E';

	A->LeftNode = B;
	A->RightNode = C;
	B->LeftNode = D;
	B->RightNode = E;

	PrevOrder(A);
	printf("\n\n");
	InOrder(A);
	printf("\n\n");
	PostOrder(A);
	return 0;
}