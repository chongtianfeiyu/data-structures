/*
    堆排序：使用优先队列来排序。
    建立N个元素的二叉堆花费O(N)时间，执行N次DeleteMin操作，每次花费O(logN)，总运行时间为O(N*logN)
    在实践中慢于（不错的序列的）希尔排序
    需要一个附加数组。也可利用第一个数组来存放，但会变成max堆。
*/
#include <stdio.h>
#include <stdlib.h>

#define ElementType double

typedef struct BinaryHeap
{
    int Capacity;
    int Size;
    ElementType * Elements;
}BinaryHeap;
typedef struct BinaryHeap * PriorityQueue;

void Insert(ElementType e, PriorityQueue P)
{
    int i;
    for (i = ++P->Size; P->Elements[i / 2] > e; i /= 2)
    {
        P->Elements[i] = P->Elements[i / 2];
    }
    P->Elements[i] = e;
}

ElementType DeleteMin(PriorityQueue P)
{
    if (P == NULL)
    {
        printf("PriorityQueue is NULL.");
        return 0;
    }
}

int main(int argc, const char *argv[])
{
    int N;
    PriorityQueue P = NULL;
    P = (PriorityQueue)malloc(sizeof(BinaryHeap));

    scanf("%d", &N);
    P->Elements = (ElementType *) malloc(sizeof(ElementType) * N);
    P->Capacity = 10000;
    P->Size = 0;

    return 0;
}
