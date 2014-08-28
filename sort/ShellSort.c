
#include <stdio.h>
#include <stdlib.h>

#define ElementType double

void ShellSort(ElementType A[], int N) {
    int i, j, Increment;
    ElementType tmp;

}

void PrintResult(ElementType A[], int N) {
    int i = N;
    while (i--)
	printf("%.1lf ", A[N - i - 1]);
    printf('\n');
}

int main(int argc, const char *argv[]) {
    int i, N = 0;
    ElementType * A = NULL;
    
    scanf("%d", &N);
    A = (ElementType *) malloc(sizeof(ElementType) * N);

    printf("Input N number: \n");

    for (i = 0; i < N; ++i)
	scanf("%lf", &A[i]);

    ShellSort(A, N);
    PrintResult(A, N);
    return 0;
}
