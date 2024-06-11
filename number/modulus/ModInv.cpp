/*
剰余環逆元アルゴリズム Inverse Element in Residue Ring Modulo Algorithm
素数pを法とする剰余環の元xについて, xの逆元を求める.
例 13を法とする剰余環において, 4の逆元は10 (4*10 = 40 = 1 mod 13)
Input:
    x: 元.
    mod: 法. xと互いに素かつxより大きくなければならない.
Output:
    y: 逆元
*/

int fastPow(int a, int b, int mod) {
    int x = 1;
    while (b > 0) {
        if (b & 1) x = (x * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return x;
}

int modInv(int x, int mod) {
    return fastPow(x, mod-2, mod);
}