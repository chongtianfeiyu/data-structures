/*
    希尔排序：比较相距一定距离的元素来工作，距离逐渐减小，直到比较相邻元素为止。so，亦叫缩小增量排序
    当只有一个增量，而这个增量为1时，即变成插入排序。
    增量序列对于希尔排序的运行时间有很大影响，流行的有（不好）：h = N/2；不错的有：2^k - 1 (1, 3, 7 ...)
    最好的是 1, 5, 19, 41...  （9 * 4^i - 9 * 2^i + 1  或  4^i - 3* 2^i + 1)
*/
#include <stdio.h>
#include <stdlib.h>

#define ElementType double

void PrintResult(ElementType A[], int N) {
    int i = N;
    while (i--)
	printf("%.1lf ", A[N - i - 1]);
    printf("\n");
}

void ShellSort(ElementType A[], int N) {
    int i, j, Increment;
    ElementType tmp;

    for (Increment = N / 2; Increment >= 1; Increment /= 2) {
        //选好增量后，使用插入排序的思想排序
		for (i = Increment; i < N; ++i) {
			tmp = A[i];
			for (j = i - Increment; j >= 0; j -= Increment) {
				if (tmp < A[j])
                    A[j + Increment] = A[j];
				else
					break;
			}
			A[j + Increment] = tmp;
		}
		PrintResult(A, N);
    }
}

int main(int argc, const char *argv[])
{
    int i, N = 0;
    ElementType * A = NULL;
    
    printf("Input N: ");
    scanf("%d", &N);
    A = (ElementType *) malloc(sizeof(ElementType) * N);

    printf("Input N number: \n");

    for (i = 0; i < N; ++i)
	scanf("%lf", &A[i]);

    ShellSort(A, N);
    PrintResult(A, N);
    return 0;
}
