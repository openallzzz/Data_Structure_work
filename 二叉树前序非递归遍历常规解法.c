//  前序遍历二叉树--非递归1
void PrevOrderNoRecursion_two(BTNode* root) {
	SqStack s;
	InitStack(&s);
	while (root || !StackEmpty(&s)) { // BUG-1

		if (root == NULL) {
			root = StackGetTop(&s);
			StackPop(&s);
			root = root->right;
		}
		if (root) { // BUG-2
			printf("%c ", root->val);
			StackPush(&s, root);
			root = root->left;
		}
	}
}