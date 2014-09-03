/*
   快速排序
*/
#include <stdio.h>
#include <stdlib.h>

#define ElementType double

void Swap(ElementType *a, ElementType *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void QuickSort(ElementType A[], int left, int right)
{
    //可以在数组较小的时候使用插入排序来减少运行时间。
    if (left >= right)
        return ;
    int i, j, center;
    center = (left + right) / 2;
    ElementType pivot;
    Swap(&A[right], &A[center]);
    pivot = A[right];
    i = left;
    j = right - 1;

    //《数据结构与算法分析》里有更好地选取枢纽元的值
    while (1)
    {
        while (A[i++] < pivot && i <= j + 1)
            ;
        while (A[j--] > pivot && j >= i - 1)
            ;
        if (i < j + 2)
            Swap(&A[i - 1], &A[j + 1]);
        else
            break;
    }
    Swap(&A[i - 1], &A[right]);
    QuickSort(A, left, i - 2);
    QuickSort(A, i, right);
}

void PrintResult(ElementType A[], int N)
{
    int i = 0;
    while (i < N)
        printf("%.1lf ", A[i++]);
    printf("\n");
}

int main(int argc, const char * argv[])
{
    int i, N;
    ElementType *A;
    printf("Input N: ");
    scanf("%d", &N);
    A = (ElementType*)malloc(sizeof(ElementType) * N);

    printf("Input N number: \n");
    i = 0;
    while (i < N)
        scanf("%lf", &A[i++]);
    
    QuickSort(A, 0, N - 1);

    PrintResult(A, N);
    return 0;
}
