/*
ユークリッドの互除法 Euclidean Algorithm
最大公約数, 最小公倍数を求める.
Input:
    x, y
output:
    (int): 最大公約数
*/

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x%y);
}

int lcm(int x, int y) {
    return (x / gcd(x, y)) * y;
}
