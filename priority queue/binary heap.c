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
    // 详解 : http://blog.chinaunix.net/uid-23629988-id-127318.html
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

void PrintPriorityQueue(PriorityQueue H) {
    int i;
    for (i = 1; i <= H->Size; i++)
	printf("%c ", H->Elements[i]);
    printf("\n");
}

int main(int argv, const ElementType *argc[]) {
    PriorityQueue H = NULL;
    H = Initialize(100);
    printf("%d\n", H->Elements[0]);

    ElementType c = 0;
    while ((c = getchar()) && c != '\n') {
	if (c != ' ') {
	    Insert(c, H);
	}
    }
    
    PrintPriorityQueue(H);
    return 0;
}
