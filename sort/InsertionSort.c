/*
    插入排序：位置0到位置P-1上的元素是已排过序的
*/

#include <stdio.h>
#include <stdlib.h>

#define ElementType double

void InsertionSort(ElementType A[], int N) {
    int i, j;

    for (i = 1; i < N; ++i) {
	ElementType temp = A[i];
	for (j = i - 1; j >= 0; --j) {
	    if (temp < A[j])
		A[j + 1] = A[j];
	    else
		break;
	}
	A[j + 1] = temp;
    }
}

void PrintResult(ElementType A[], int N) {
    int i = N;
    while (i--)
	printf("%.1lf ", A[N - i - 1]);
    printf("\n");
}

int main(int argc, const char *argv[]) {
    int i, N = 0;
    ElementType * A = NULL;
    printf("Input N :");
    scanf("%d", &N);
    A = (ElementType*) malloc(sizeof(ElementType) * N);
    printf("Input N number:\n");
    for (i = 0; i < N; ++i)
	scanf("%lf", &A[i]);

    InsertionSort(A, N);
    PrintResult(A, N);
    return 0;
}
