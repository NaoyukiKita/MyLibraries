/*
冪乗の高速演算アルゴリズム Fast Power Algorithm
a^bを高速に演算する
Input:
    a, b: 底と指数
Output:
    a^b
*/

int fastPow(int a, int b) {
    int x = 1;
    while (b > 0) {
        if (b & 1) x *= a;
        a *= a;
        b >>= 1;
    }
    return x;
}

int fastPow(int a, int b, int mod) {
    int x = 1;
    while (b > 0) {
        if (b & 1) x = (x * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return x;
}