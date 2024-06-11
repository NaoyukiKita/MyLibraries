/*
不定方程式アルゴリズム Bézout's solver
一次不定方程式(Bézout's identity): ax + by = cを解く.
例 37x + 61y = 16 -> x=21, y=13
Input:
    a, b, c: cはa, bの最大公約数の倍数でなければならない
    x, y: 解を格納する変数
Output: Null
*/

int extGCD(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    int d = extGCD(b, a%b, y, x);
    y -= a/b * x;
    return d;
}

void bezout(int a, int b, int c, int&x, int&y) {
    int gcd = extGCD(a, b, x, y);
    x *= c / gcd;
    y *= c / gcd;
    while ((x > y ? x-y : y-x) > a+b) {
        x -= (2*(x > y)-1) * b;
        y += (2*(x > y)-1) * a;
    }
    return;
}
