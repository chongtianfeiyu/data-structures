#include <stdio.h>
#include <stdlib.h>

#ifndef _AVL_TREE_H

// struct AvlNode;
typedef struct AvlNode * Position;
typedef struct AvlNode * AvlTree;

Position Find(char c, AvlTree T);
AvlTree Delete(char c, AvlTree T);
AvlTree Insert(char c, AvlTree T);
AvlTree SingleRotateWithLeft(AvlTree T);
AvlTree DoubleRotateWithLeft(AvlTree T);
AvlTree SingleRotateWithRight(AvlTree T);
AvlTree DoubleRotateWithRight(AvlTree T);

#endif

typedef struct AvlNode
{
	char Element;
	AvlTree Left;
	AvlTree Right;
	int Height;
}AvlNode;

static int Height(AvlTree T)
{
    if (T == NULL)
        return -1;
    return T->Height;
}

inline int Max(int left, int right) {
	return left > right ? left : right;
}

AvlTree Insert(char c, AvlTree T) {
	if (T == NULL) {
		//要是不加 stdlib.h ， 会使用内联的malloc函数，在转换时会有警告
		T = (AvlNode *) malloc(sizeof(AvlNode));
		if (T == NULL)
			printf("Out of space!\n");
		else {
			T->Element = c;
			T->Left = T->Right = NULL;
			T->Height = 0;
		}
	}
	else if (T->Element > c) {
		T->Left = Insert(c, T->Left);
		if (Height(T->Left) - Height(T->Right) >= 2)     
			if (c < T->Left->Element)
				T = SingleRotateWithLeft(T);
			else
				T = DoubleRotateWithLeft(T);
	}
	else if (T->Element < c) {
		T->Right = Insert(c, T->Right);
		if (Height(T->Right) - Height(T->Left) >= 2)
			if (c > T->Right->Element)
				T = SingleRotateWithRight(T);
			else
				T = DoubleRotateWithRight(T);
	}

	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

AvlTree Delete(char c, AvlTree T) {
	if (c < T->Element) {
		Delete(c, T->Left);
		if (Height(T->Right) - Height(T->Left) >= 2) {

			T->Height = Max(Height(T->Left), Height(T->Right)) - 1;
		}
	}
	else if (c > T->Element) {
		Delete(c, T->Right);
		if (Height(T->Right) - Height(T->Left) >= 2) {

			T->Height = Max(Height(T->Left), Height(T->Right)) - 1;
		}
	}
	else {
		printf("No such element!");
		return T;
	}
	
}
//left-left : 单次旋转即可恢复平衡
AvlTree SingleRotateWithLeft(AvlTree T) {
	Position head = T->Left;
	T->Left = head->Right;
	head->Right = T;
	
	//别忘记高度的变化(一开始忘了...)
	T->Height = Max(Height(T->Left), Height(T->Right));
	head->Height = Max(Height(head->Left), Height(head->Right));
	return head;
}
//left-right : 双旋转才能恢复平衡(书上用两次单旋转就解决了，可以看看)	
AvlTree DoubleRotateWithLeft(AvlTree T) {
	Position head = T->Left->Right;
	Position left = T->Left;
	left->Right = head->Left;
	T->Left = head->Right;
	head->Left = left;
	head->Right = T;

	left->Height = Max(Height(left->Left), Height(left->Right));
	T->Height = Max(Height(T->Left), Height(T->Right));
	head->Height = Max(Height(head->Left), Height(head->Right));
	return head;
}

AvlTree SingleRotateWithRight(AvlTree T) {
	Position head = T->Right;
	T->Right = head->Left;
	head->Left = T;

	T->Height = Max(Height(T->Left), Height(T->Right));
	head->Height = Max(Height(head->Left), Height(head->Right));
	return head;
}

AvlTree DoubleRotateWithRight(AvlTree T) {
	Position head = T->Right->Left;
	Position right = T->Left->Right;
	
	right->Left = head->Right;
	T->Right = head->Left;
	head->Left = T;
	head->Right = right;

	right->Height = Max(Height(right->Left), Height(right->Right));
	T->Height = Max(Height(T->Left), Height(T->Right));
	head->Height = Max(Height(head->Left), Height(head->Right));
	return head;
}

void PrintTree(AvlTree T) {
    if (T == NULL)
        return ;
    PrintTree(T->Left);
    printf("%c ", T->Element);
    PrintTree(T->Right);
}

void PrintPreTree(AvlTree T) {
    if (T == NULL)
        return ;
    printf("%c ", T->Element);
    PrintPreTree(T->Left);
    PrintPreTree(T->Right);
}

int main(int argc, char const *argv[])
{
    AvlTree T = NULL;
    T = Insert('a', T);
    T = Insert('b', T);
    T = Insert('c', T);
    T = Insert('z', T);
    PrintPreTree(T);
    PrintTree(T);
    return 0;
}
