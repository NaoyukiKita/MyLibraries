/*
素因数分解 Factorization Algorithm
Input:
    x
    primes: 素因数を格納するvector. 要素数=0
Output: Null
*/

#include <vector>
using namespace std;

void factorize(int x, vector<int>& primes) {
    while (!(x & 1)) {
        primes.push_back(2);
        x >>= 1;
    }
    for (int p = 3; p*p <= x; p+= 2) {
        while (x % p == 0) {
            primes.push_back(p);
            x /= p;
        }
    }
    if (x != 1) primes.push_back(x);
}