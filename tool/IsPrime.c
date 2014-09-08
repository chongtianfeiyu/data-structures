/*
    费马小定理：如果P是素数，且0 < A < P,那么 A^(P-1) === 1 (mod P) ( "===" 为同余).
    当余数不等于1时，肯定不是素数，若等于一，则可能是素数。
    所以需要用到下一个定理。
    定理：如果 P 是素数且0 < X < P, 那么 X^2 === 1 (mod P) 仅有的两个解为 X = 1, P-1.
    
    注意：该算法至少有75%的几率结果正确，若对一个数测试50次(A随机)，正确率极高。
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef long long HugeInt;

int Prime(HugeInt A, HugeInt i, HugeInt N)
{
    HugeInt x, y;

    if (i == 0)
        return 1;

    if (i == 1)
        return A;

    x = Prime(A, i / 2, N);
    if (x == 0)
        return 0;

    //第二个定理
    y = (x * x) % N;
    if (y == 1 && x != 1 && x != N - 1)
        return 0;

    if (i % 2)
        y = (A * y) % N;

    return y;
}

int IsPrime(HugeInt N)
{
    int i, correct, wrong, result;
    correct = wrong = result = 0;
    //测试50次，保证正确率。
    for ( i = 1; i <= 50; ++i)
    {
        result = Prime(RandInt(2, N - 1, i), N - 1, N) == 1;
        if (result)
            ++correct;
        else
            ++wrong;
    }
    return correct > wrong ? 1 : 0;
}

//产生伪随机数。
int RandInt(int x, int y, int seed)
{
    srand(seed);
    return (int) (x + rand() % (y - x + 1));
}


int main(int argc, const char* argv[])
{
    int N;
    while (scanf("%d", &N) != EOF)
        printf("result : %d\n", IsPrime(N));
    return 0;
}
