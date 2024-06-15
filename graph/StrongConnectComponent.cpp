/*
強連結成分アルゴリズム Strongly Connected Component Algorithm
有向グラフの強連結成分を求め, 各点がどの強連結成分に属するかを示す.
Input:
    links: links[u]が頂点uから1回の移動で到達可能な頂点のvectorであるような2次元vector.
    rev_links: links[u]が頂点uへ1回の移動で到達可能な頂点のvectorであるような2次元vector.
    res: 返却値を格納するvector. res[u]=uが属する強連結成分のid. 要素数=頂点数.
Output: Null
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void visit1(vector<vector <int> >& links,
    vector<bool>& visited,
    vector<int>& inv_phi,
    int v, int& N) {
    visited[v] = true;
    for (int w : links[v]) {
        if (visited[w]) continue;
        visit1(links, visited, inv_phi, w, N);
    }
    inv_phi[N++] = v;
}

void visit2(vector<vector <int> >& rev_links,
    vector<bool>& visited,
    vector<int>& res,
    int v, int& K) {
    visited[v] = true;
    for (int w : rev_links[v]) {
        if (visited[w]) continue;
        visit2(rev_links, visited, res, w, K);
    }
    res[v] = K;
}

void SCC(vector<vector <int> >& links,
    vector<vector <int> >& rev_links,
    vector<int>& res) {

    int n = links.size();
    int N = 0;
    queue<int> que;
    vector<bool> visited(n);
    vector<int> inv_phi(n);
    for (int v = 0; v < n; v++) {
        if (visited[v]) continue;
        visit1(links, visited, inv_phi, v, N);
    }
    visited = vector<bool>(n);
    int K = 0;
    for (int v = n-1; v >= 0; v--) {
        if (visited[v]) continue;
        visit2(rev_links, visited, res, v, K);
        K++;
    }
}

// usecase
int main() {
    int N, M, a, b;
    cin >> N >> M;
    
    vector<vector <int> > links(N, vector<int>());
    vector<vector <int> > rev_links(N, vector<int>());
    for (int m = 0; m < M; m++) {
        cin >> a >> b;
        links[a].push_back(b);
        rev_links[b].push_back(a);
    }
    
    vector<int> res(N);
    SCC(links, rev_links, res);
    
    for (int i = 0; i < N; i++) {
        cout << res[i] << " \n"[i == N-1];
    }
}