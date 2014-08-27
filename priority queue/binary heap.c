/*
    优先队列（堆）使用二叉堆实现。
    二叉堆，又名完全二叉树，元素依次从左往右，从上往下填入。
    根据其结构性，可用数组实现。
    堆排序会用到。
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef _BinHeap_H
#define bool int
#define ElementType int

typedef struct HeapStruct
{
   int Capacity;
   int Size;
   ElementType * Elements;
}HeapStruct;

typedef struct HeapStruct * PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Insert(ElementType c, PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
bool IsEmpty(PriorityQueue H);
bool IsFull(PriorityQueue H);

#endif

//初始化二叉堆
PriorityQueue Initialize(int MaxElements) {
    PriorityQueue H = (PriorityQueue) malloc(sizeof(struct HeapStruct));
    if (H == NULL) {
	printf("out of space!");
	return H;
    }
    
    H->Elements = (ElementType *) malloc(sizeof(MaxElements + 1));
    if (H->Elements == NULL) {
	printf("out of space!");
	return H;
    }

    H->Capacity = MaxElements;
    H->Size = 0;
    // "1 << (sizeof(ElementType) * 8)" , gcc 给 warning : left shift count >= width of type 
    // 问题详解 : http://blog.chinaunix.net/uid-23629988-id-127318.html
    // 作用：得出最小值，放在Elements[0]处，用于停止比较
    H->Elements[0] = 1 << (sizeof(ElementType) * 8 - 1);
    return H;
}

bool IsFull(PriorityQueue H) {
    return H->Capacity >= H->Size ? 0 : 1;
}

bool IsEmpyt(PriorityQueue H) {
    return H->Size ? 1 : 0;
}

void Insert(ElementType c, PriorityQueue H) {
    if (IsFull(H)) {
	printf("Full\n");
	return ;
    }
    int i;
    for (i = ++H->Size; H->Elements[i / 2] > c; i /= 2)
	H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = c;
}

ElementType DeleteMin(PriorityQueue H) {
    if (H == NULL) {
        printf("PriorityQueue is NULL");
        return 0;
    }

    ElementType result = H->Elements[1];
    //长度已经减一！
    ElementType lastElement = H->Elements[H->Size--];
    int i, child;
    for (i = 1; i * 2<= H->Size; i = child) {
	//child定位较小的值的位置
	child = i * 2;
	if (child != H->Size && H->Elements[child + 1] < H->Elements[child])
	    child++;
	
	//判断最后元素是否插入
	if (lastElement > H->Elements[child])
	    H->Elements[i] = H->Elements[child];
	else
	    break;
    }
    H->Elements[i] = lastElement;
    return result;
}

void Swap(ElementType * a, ElementType * b) {
    ElementType t = *a;
    *a = *b;
    *b = t;
}

//将普通二叉树变为二叉堆
void BuildHeap(PriorityQueue H) {
    int i = H->Size;
    for (i /= 2; i >= 1; i--) {
    	int father, child;
	ElementType f = H->Elements[i];

	for (father = i; father * 2 <= H->Size; father = child) {
	    child = father * 2;
	    //确定左儿子较小还是右儿子较小
	    if (child != H->Size && H->Elements[child + 1] < H->Elements[child] )
	        child++;
	    //
	    if (f > H->Elements[child])
	        H->Elements[father] = H->Elements[child];
	    else
	        break;
	}
	H->Elements[father] = f;
    }
}

void PrintPriorityQueue(PriorityQueue H) {
    int i;
    for (i = 1; i <= H->Size; i++)
	printf("%d ", H->Elements[i]);
    printf("\n");
}

int main(int argv, const ElementType *argc[]) {
    PriorityQueue H = NULL;
    H = Initialize(100);
    int i = 1;
    while (i < 15)
    	//Elements[i++] = 100 - i : 结果为[1, 2, 3 ...] = 99, 98, 97 ...
	//Elements[i] = 100 - i++ : 同上
	//Elements[++i] = 100 - i : [1, 2, 3 ...] = 0, 98, 97 ...
	//Elements[i] = 100 - ++i : [1, 2, 3 ...] = 98, 97, 96 ...
        H->Elements[i++] = 100 - i;
    H->Size = 14;
    PrintPriorityQueue(H);

    BuildHeap(H);
    PrintPriorityQueue(H);

    ElementType c = 0;
    while ((c = getchar()) && c != '\n') {
	if (c != ' ') {
	    Insert(c, H);
	}
    }
    PrintPriorityQueue(H);
    i = 1;
    while (i < 15)
        printf("%d : %d\n", i++, DeleteMin(H));
    PrintPriorityQueue(H);
    return 0;
}
