
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char * Type;

/*
   Longest Common Subsequence(最长公共子序列)
   应该能用字符串匹配的算法(KMP算法)进行优化。
*/
void LCS(Type A, const int lenA, Type B, const int lenB)
{
    int aCursor, bCursor, aBegin, MaxLen;
    int endA, endB;
    MaxLen = 0;
    for (aCursor = 0; aCursor < lenA; ++aCursor)
    {
        for (bCursor = 0; bCursor < lenB; ++bCursor)
        {
            if (A[aCursor] == B[bCursor])
            {
                endA = aCursor;
                endB = bCursor;
                while (++endA < lenA && ++endB < lenB && A[endA] == B[endB])
                    ;
                if (MaxLen < endA - aCursor)
                {
                    MaxLen = endA - aCursor;
                    aBegin = aCursor;
                }
            }
        }
    }
    for (aCursor = aBegin; aCursor < aBegin + MaxLen; ++aCursor)
        printf("%c ", A[aCursor]);
    printf("\n");
}

int main(int argc, const char* argv[])
{
    Type A, B;
    int i = 5000;
    printf("Input string A:\n");
    A = (Type)malloc(sizeof(char) * i);
    scanf("%s", A);
    printf("Input string B:\n");
    B = (Type)malloc(sizeof(char) * i);
    scanf("%s", B);
    
    LCS(A, strlen(A), B, strlen(B));
    
    return 0;
}
