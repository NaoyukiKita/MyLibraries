/*
素因数分解 Factorization Algorithm
Input:
    x
    primes: 素因数を格納するvector. 要素数=0
Output: Null
*/

#include <vector>
#include <map>
using namespace std;
using ll = long long int;

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

map<ll, int> factorize(ll N) {
    map<ll, int> m;
    ll ub = ll(sqrt(double(N)));
    for (; !(N & 1); N >>= 1) m[2]++;
    for (ll p = 3; N-1 && p <= ub; p += 2) {
        for (; !(N%p); N /= p) m[p]++;
    } if (N-1) m[N]++;
    
    return m;
}