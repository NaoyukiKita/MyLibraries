/*
グラフ走査アルゴリズム Graph Scanning Algorithm
開始地点から到達可能な頂点集合を求める(逆方向へのパスはなくても可). 開始地点自身も含める.
Input:
    links: links[u]が頂点uから1回の移動で到達可能な頂点のvectorであるような2次元vector.
    res: 返却値を格納するvector. 要素数0.
    s: 開始地点を指す頂点.
Output: Null
*/

#include <vector>
#include <queue>
using namespace std;

void graphScan(vector<vector <int> >& links, vector<int>& res, int s) {
    vector<bool> visited(links.size());
    res.push_back(s);
    queue<int> que;
    que.push(s);
    while (!que.empty()) {
        int cur = que.front(); que.pop();
        visited[cur] = true;
        for (int neighbor : links[cur]) {
            if (visited[neighbor]) continue;
            res.push_back(neighbor);
        }
    }
}