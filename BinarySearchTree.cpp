#include <iostream>

struct Node
{
	int data;
	Node *left, *right;
};

Node *newNode(int data)
{
	Node *n = (Node *)malloc(sizeof(Node));
	n->data = data;
	n->left = n->right = NULL;

	return n;
}

int search(Node *root, int key)
{
	if (root == NULL)
		return 0;

	if (root->data == key)
		return 1;

	if (root->data > key)
		return search(root->left, key);
	else
		return search(root->right, key);
}

int height(Node *root)
{
	if (root == NULL)
		return -1;

	int lHeight = height(root->left);
	int rHeight = height(root->right);

	if (lHeight > rHeight)
		return lHeight + 1;
	else
		return rHeight + 1;
}

void printCurrentLevel(Node *root, int level)
{
	if (root == NULL)
		return;
	if (level == 0)
		printf("%d ", root->data);
	else
	{
		printCurrentLevel(root->left, level - 1);
		printCurrentLevel(root->right, level - 1);
	}
}

void printLevelOrder(Node *root)
{
	int h = height(root);

	for (int i = 0; i <= h; i++)
	{
		printCurrentLevel(root, i);
		std::cout << std::endl;
	}
}

void insert(Node **root, int data)
{
	Node *n = newNode(data);

	if (*root == NULL)
	{
		*root = n;
		return;
	}

	if ((*root)->data == data)
		return;

	if ((*root)->data > data)
	{
		if ((*root)->left == NULL)
		{
			(*root)->left = n;
		}
		else
		{
			free(n);
			insert(&((*root)->left), data);
		}
	}
	else
	{
		if ((*root)->right == NULL)
		{
			(*root)->right = n;
		}
		else
		{
			free(n);
			insert(&((*root)->right), data);
		}
	}
}

void deleteNode1(Node **root, int key)
{
	Node *front = *root;
	Node *back = NULL;

	if (*root == NULL)
		return;

	while (front->data != key)
	{
		back = front;

		if (front->data > key)
			front = front->left;
		else
			front = front->right;

		if (front == NULL)
			return;
	}

	if (front->left == NULL)
	{
		if (front != *root)
		{
			if (back->left == front)
				back->left = front->right;
			else
				back->right = front->right;
		}
		else
		{
			*root = front->right;
		}

		free(front);
	}
	else if (front->right == NULL)
	{
		if (front != *root)
		{
			if (back->left == front)
				back->left = front->left;
			else
				back->right = front->left;
		}
		else
		{
			*root = front->left;
		}

		free(front);
	}
	else
	{
		Node *succBack = NULL;
		Node *succ = front->right;

		while (succ->left != NULL)
		{
			succBack = succ;
			succ = succ->left;
		}

		front->data = succ->data;

		if (succ == front->right)
			front->right = succ->right;
		else
			succBack->left = succ->right;

		free(succ);
	}
}

void avlBalance(Node **root)
{
	if (*root == NULL)
		return;

	avlBalance(&(*root)->left);
	avlBalance(&(*root)->right);

	int b = height((*root)->left) - height((*root)->right);

	if (b > 1)
	{
		Node *x = *root;
		Node *y = x->left;
		Node *sub1 = y->left;
		Node *sub2 = y->right;
		Node *sub3 = x->right;

		*root = y;
		y->left = sub1;
		y->right = x;
		x->left = sub2;
		x->right = sub3;
	}
	else if (b < -1)
	{
		Node *x = *root;
		Node *y = x->right;
		Node *sub1 = y->right;
		Node *sub2 = y->left;
		Node *sub3 = x->left;

		*root = y;
		y->left = x;
		y->right = sub1;
		x->left = sub3;
		x->right = sub2;
	}
}

void avlInsert(Node **root, int data)
{
	insert(root, data);

	avlBalance(root);
}

int main()
{
	Node *n = newNode(13);
	//n->left = newNode(20);
	//n->right = newNode(40);
	//n->left->left = newNode(10);
	//n->left->right = newNode(25);
	//n->right->left = newNode(35);
	//n->right->right = newNode(50);
	//insert(&n, 22);
	//insert(&n, 26);
	//insert(&n, 23);
	//insert(&n, 38);

	avlInsert(&n, 10);
	avlInsert(&n, 6);
	avlInsert(&n, 5);
	avlInsert(&n, 4);
	avlInsert(&n, 15);
	avlInsert(&n, 16);
	avlInsert(&n, 11);

	printLevelOrder(n);
}
