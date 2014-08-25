#include <stdio.h>
#include <math.h>


#ifndef _BinHeap_H

typedef struct HeapStruct
{
   int Capacity;
   int Size;
   char * Elements;
}HeapStruct;

typedef struct HeapStruct * PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Insert(char c, PriorityQueue H);
char DeleteMin(PriorityQueue H);
char FindMin(PriorityQueue H);
bool IsEmpty(PriorityQueue H);
bool IsFull(PriorityQueue H);

#endif

PriorityQueue Initialize(int MaxElements) {
    PriorityQueue H = (PriorityQueue) malloc(sizeof(struct HeapStruct));
    if (H == NULL) {
	printf("out of space!");
	return H;
    }
    
    H->Elements = (char *) malloc(sizeof(MaxElements + 1));
    if (H->Elements == NULL) {
	printf("out of space!");
	return H;
    }

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Elements[0] = (~0) * -1;
    return H;
}

bool IsFull(PriorityQueue H) {
    return H->Capacity >= H->Size ? false : true;
}

bool IsEmpyt(PriorityQueue H) {
    return H->Size ? true : false;
}

void Insert(char c, PriorityQueue H) {
    if (IsFull(H)) {
	printf("Full\n");
	return ;
    }
    int i;
    for (i = ++H->Size; H->Elements[i / 2] > c; i /= 2)
	H->Elements[i] = H->Elements[i / 2];
    H->Elements[i] = c;
}

char DeleteMin(PriorityQueue H) {
    if (H == NULL) {
        printf("PriorityQueue is NULL");
        return '';
    }

    char result = H->Elements[1];
    //长度已经减一！
    char lastElement = H->Elements[H->Size--];
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
    for (int i = 1; i < H->Size; i++)
	printf("%c ", H->Elements[i]);
}

int main(int argv, const char *argc[]) {
    PriorityQueue H = NULL;
    H = Initialize(100);

    Insert('a', H);
    Insert('b', H);
    Insert('c', H);

    PrintPriorityQueue(H);
    return 0;
}
