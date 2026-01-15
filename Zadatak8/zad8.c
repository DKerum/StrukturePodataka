#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _tree* treePtr;
typedef struct _tree {
	int value;
	treePtr left;
	treePtr right;
} tree;

tree* NewTree(int value) {
	tree* t = (tree*)malloc(sizeof(tree));
	t->value = value;
	t->left = NULL;
	t->right = NULL;
	return t;
}

tree* Add(tree* root, int x) {
	if (root == NULL)
		return NewTree(x);

	if (x < root->value)
		root->left = Add(root->left, x);
	else if (x > root->value)
		root->right = Add(root->right, x);

	return root;
}

void PrintIn(tree* root) {
	if (root) {
		PrintIn(root->left);
		printf("%d ", root->value);
		PrintIn(root->right);
	}
}

void PrintPre(tree* root) {
	if (root) {
		printf("%d ", root->value);
		PrintPre(root->left);
		PrintPre(root->right);
	}
}

void PrintPost(tree* root) {
	if (root) {
		PrintPost(root->left);
		PrintPost(root->right);
		printf("%d ", root->value);
	}
}

int TreeHeight(tree* root) {
	if (!root) return 0;
	int l = TreeHeight(root->left);
	int r = TreeHeight(root->right);
	return (l > r ? l : r) + 1;
}

void PrintLevel(tree* root, int lvl) {
	if (!root) return;
	if (lvl == 1)
		printf("%d ", root->value);
	else {
		PrintLevel(root->left, lvl - 1);
		PrintLevel(root->right, lvl - 1);
	}
}

void LevelOrder(tree* root) {
	int h = TreeHeight(root);
	for (int i = 1; i <= h; i++)
		PrintLevel(root, i);
}

int Find(tree* root, int x) {
	if (!root) return 0;
	if (root->value == x) return 1;
	if (x < root->value) return Find(root->left, x);
	return Find(root->right, x);
}

tree* MinTree(tree* root) {
	while (root && root->left)
		root = root->left;
	return root;
}

tree* Remove(tree* root, int x) {
	if (!root) return root;

	if (x < root->value)
		root->left = Remove(root->left, x);
	else if (x > root->value)
		root->right = Remove(root->right, x);
	else {
		if (!root->left) {
			tree* temp = root->right;
			free(root);
			return temp;
		}
		else if (!root->right) {
			tree* temp = root->left;
			free(root);
			return temp;
		}
		tree* temp = MinTree(root->right);
		root->value = temp->value;
		root->right = Remove(root->right, temp->value);
	}
	return root;
}

int main() {
	tree* root = NULL;

	/*int arr[] = {1,9,5,12,8,6,4};
	int size = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < size; i++)
		root = Add(root, arr[i]);*/

	int option, num;

	do {
		printf("\n1. Dodaj element\n");
		printf("2. Ispis (inorder)\n");
		printf("3. Ispis (preorder)\n");
		printf("4. Ispis (postorder)\n");
		printf("5. Ispis (level order)\n");
		printf("6. Pronadi element\n");
		printf("7. Izbrisi element\n");
		printf("8. Izlaz\n");
		printf("Unesi izbor: ");
		scanf("%d", &option);

		switch (option) {
		case 1:
			printf("Unesi vrijednost: ");
			scanf("%d", &num);
			root = Add(root, num);
			break;
		case 2:
			PrintIn(root); printf("\n");
			break;
		case 3:
			PrintPre(root); printf("\n");
			break;
		case 4:
			PrintPost(root); printf("\n");
			break;
		case 5:
			LevelOrder(root); printf("\n");
			break;
		case 6:
			printf("Trazi: ");
			scanf("%d", &num);
			printf(Find(root, num) ? "Pronaden\n" : "Nema ga\n");
			break;
		case 7:
			printf("Brisi: ");
			scanf("%d", &num);
			root = Remove(root, num);
			break;
		case 8:
			printf("Kraj\n");
			break;
		default:
			printf("Pogresan unos\n");
		}
	} while (option != 8);

	return 0;
}
