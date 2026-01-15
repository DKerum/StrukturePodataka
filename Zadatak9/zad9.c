#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _tree {
	int data;
	struct _tree* left;
	struct _tree* right;
} tree;

tree* CreateTree(int data) {
	tree* t = (tree*)malloc(sizeof(tree));
	t->data = data;
	t->left = NULL;
	t->right = NULL;
	return t;
}

tree* Add(tree* root, int data) {
	if (root == NULL)
		return CreateTree(data);

	if (data <= root->data)
		root->left = Add(root->left, data);
	else
		root->right = Add(root->right, data);

	return root;
}

int ReplaceValues(tree* root) {
	if (root == NULL)
		return 0;

	int sumL = ReplaceValues(root->left);
	int sumR = ReplaceValues(root->right);
	int old = root->data;

	root->data = sumL + sumR;
	return old + root->data;
}

void PrintInOrder(tree* root, FILE* f) {
	if (root == NULL)
		return;

	PrintInOrder(root->left, f);
	fprintf(f, "%d ", root->data);
	PrintInOrder(root->right, f);
}

int main() {

	int arr[] = { 2,5,7,8,11,1,4,2,3,7 };
	int i, n = sizeof(arr) / sizeof(arr[0]);
	FILE* f;

	tree* root = NULL;
	for (i = 0; i < n; i++)
		root = Add(root, arr[i]);

	/* pod a) */
	f = fopen("InOrder_a.txt", "w");
	if (!f) {
		printf("Greska 1");
		return 1;
	}
	PrintInOrder(root, f);
	fclose(f);

	/* pod b) */
	ReplaceValues(root);
	f = fopen("InOrder_b.txt", "w");
	if (!f) {
		printf("Greska 2");
		return 1;
	}
	PrintInOrder(root, f);
	fclose(f);

	/* pod c) */
	srand((unsigned)time(NULL));
	tree* randRoot = NULL;

	for (i = 0; i < n; i++) {
		int rnd = 10 + rand() % 81;
		randRoot = Add(randRoot, rnd);
	}

	f = fopen("InOrder_c.txt", "w");
	if (!f) {
		printf("Greska 3");
		return 1;
	}
	PrintInOrder(randRoot, f);
	fclose(f);

	return 0;
}
