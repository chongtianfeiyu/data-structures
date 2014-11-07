#include <iostream>
#include <stdio.h>

using namespace std;

/*
   给一个数n，输出n的二进制有多少个1。
   n & (n - 1) 的值刚好是n最右边的1为0的值。
*/
int numberOf1(int n) {
    int num = 0;
    while (n) {
        num++;
        n &= n - 1;
    }
    return num;
}

int main(void) {
    printf("%x\n", 124325);
    cout << numberOf1(124325) << endl;
    return 0;
}
