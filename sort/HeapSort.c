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
        exit(1);
    }
    if (P->Size <= 0)
    {
        printf("No");
        exit(2);
    }
    int i, child;
    ElementType result = P->Elements[1];
    ElementType lastElement = P->Elements[P->Size--]; //长度已减
    
    for (i = 1; i * 2 <= P->Size; i = child)
    {
        child = i * 2;
        //选出两儿子之中较小的儿子的位置，child记录
        if (child <= P->Size && P->Elements[child] > P->Elements[child + 1])
            child += 1;

        if (lastElement > P->Elements[child])
            P->Elements[i] = P->Elements[child];
        else
            break;
    }
    P->Elements[i] = lastElement;

    //PrintArray("after delete", P->Elements, 1, P->Size);
    return result;
}

void PrintArray(const char* message, ElementType A[], int begin, int end)
{
    int i;
    printf("%s : ", message);
    for (i = begin; i < end; ++i)
        printf("%0.1lf ", A[i]);
    printf("\n");
}

int main(int argc, const char *argv[])
{
    int N;
    PriorityQueue P = NULL;
    P = (PriorityQueue)malloc(sizeof(BinaryHeap));

    scanf("%d", &N);
    P->Elements = (ElementType *) malloc(sizeof(ElementType) * (N + 1));
    P->Capacity = N + 1;
    P->Size = 0;
    
    int i;
    ElementType t;
    for (i = 1; i <= N; ++i)
    {
        scanf("%lf", &t);
        Insert(t, P);
    }
    PrintArray("all", P->Elements, 1, N + 1);

    while (N--)
        printf("%0.1lf ", DeleteMin(P));
    printf("\n");
    return 0;
}
