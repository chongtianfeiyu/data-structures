/*
   归并排序：最坏情形运行时间为O(N*logN)，所使用的比较次数几乎最优。
   使用的是分治策略。
   不适用于主存排序，因为合并需要额外的内存。
 */

#include <stdio.h>
#include <stdlib.h>

#define ElementType double

void PrintResult(ElementType A[ ], int N)
{
    int i = 0;
    while (i < N)
        printf("%0.1lf ", A[i++]);
    printf("\n");
}

void Merge(ElementType A[], ElementType tmpArray[], int left, int center, int right)
{
    int i = left, j = center;
    int t = left;

    while (1)
    {
        if (i < center && j <= right)
        {
            if (A[i] < A[j])
                tmpArray[t++] = A[i++];
            else
                tmpArray[t++] = A[j++];
        }
        //剩余一边数组的话，直接记录到临时数组
        else if (i < center)
        {
            while (i < center)
                tmpArray[t++] = A[i++];
            break;
        }
        else if (j <= right)
        {
            while (j <= right)
                tmpArray[t++] = A[j++];
            break;
        }
        else
            break;
    }
    //将临时数组数据读回数组 A
    while (left <= right)
    {
        A[left] = tmpArray[left++];
    }
}

void MSort(ElementType A[], ElementType tmpArray[], int left, int right)
{
    if (left >= right)
    {
        return ;
    }
    int center = (left + right) / 2;
    //左排序，右排序，最后合并
    MSort(A, tmpArray, left, center);
    MSort(A, tmpArray, center + 1, right);
    Merge(A, tmpArray, left, center + 1, right);
}

void MergeSort(ElementType A[], int N)
{
    ElementType *tmpArray = (ElementType*)malloc(sizeof(ElementType) * N);
    if (tmpArray != NULL)
    {
        MSort(A, tmpArray, 0, N - 1);
        free(tmpArray);
    }
    else
        printf("No space for tmpArray\n");
}

int main(int argc, const char* argv[])
{
    int i, N;
    printf("Input N: ");
    scanf("%d", &N);

    ElementType *A = (ElementType*) malloc(sizeof(ElementType) * N);

    printf("Input N's numbers: \n");
    for (i = 0; i < N; ++i)
    {
        scanf("%lf", &A[i]);
    }
    MergeSort(A, N);

    PrintResult(A, N);
    return 0;
}
