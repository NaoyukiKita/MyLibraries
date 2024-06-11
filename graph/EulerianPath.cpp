/*
Euler路作成アルゴリズム Euler's Algorithm
無向連結EulerグラフのEuler路を作成する.
Input:
    links: links[u]が頂点uと隣接した頂点のvectorであるような2次元vector.
    trail: 作成されたEuler路を格納するvector. 要素数=頂点数.
Output: Null
*/

#include <vector>
using namespace std;

void SemiEulerTrail(vector<vector<int> >& links,
    vector<int>& trail,
    int s, int t, int cur) {
    for (int i = 0; i < links[s].size(); i++) {
        
    }
}