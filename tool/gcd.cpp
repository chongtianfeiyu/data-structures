#include <iostream>
#include <time.h>

using namespace std;

inline void Swap(unsigned int& a, unsigned int& b) { a ^= b; b ^= a; a ^= b; }

/*
   求最大公约数的方法（编程之美）
*/
unsigned int gcd(unsigned int a, unsigned int b) {
    if (a <= 0 && b <= 0)
        return 0;
    if (a < b)
        Swap(a, b);

    int count = 0;
    unsigned int ta = a, tb = b;
    /*
       辗转相除法求最大公约数(gcd)
       缺点：求余耗的时间长
    */
    while (b > 0) {
        a %= b;
        Swap(a, b);
        count++;
    }
    cout << a << endl;
    //return a;

    count = 0;
    a = ta, b = tb;
    /*
       基于这样的事实：(f(x,y)为x和y的最大公约数)
       1、f(x, y) = f(x, x-y); (令x > y)
       2、p为素数, x=p*k, y不能被p整除, 有f(x, y) = f(x/p, y);
       3、若x、y都能被k整除, f(x, y) = f(x/k, y/k);
       令素数为2
   */
    while (b > 0) {
        //两个数都为奇时，用事实1，可得到一数为偶
        if (a & 0x1 && b & 0x1) {
            a -= b;
            if (a < b)
                Swap(a, b);
        }
        //一奇一偶时，用事实2
        if (a & 1 && !(b & 1)) {
            b >>= 1;
        }
        else if (!(a & 1) && b & 1) {
            a >>= 1;
            if (a < b)
                Swap(a, b);
        }
        //都为偶时，用事实3
        else if (!(a & 1) && !(b & 1)) {
            a >>= 1;
            b >>= 1;
        }
        count++;
    }
    cout << a << endl;
    return a;
}

int main(void)
{
    gcd(4134567890, 3572931);
    return 0;
}
