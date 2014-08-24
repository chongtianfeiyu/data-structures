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
void Inset(char c, PriorityQueue H);
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

void Inset(char c, PriorityQueue H) {
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
    
    int maxPosition = FindMax(PriorityQueue H);
    int i = 0;
    int i = H->Size;
    if (i == 1) {
	H->Size--;
	return result;
    }
    else if (i & 1) {
        while (i > 1) {
	    char temp = H->Elements[i / 2];
	    H->Elements[i / 2] = H->Elements[i] > H->Elements[i - 1] ? H->Elements[i - 1] : H->Elements[i];
	    i /= 2;
        }
    }
    else {
	while (i > 1) {
            char temp = H->Elements[i / 2];
	    H->Elements[i / 2] = H->Elements[i] > H->Elements[i - 1] ? H->Elements[i - 1] : H->Elements[i];
	    i /= 2;
	}
    }

    return result;
}


