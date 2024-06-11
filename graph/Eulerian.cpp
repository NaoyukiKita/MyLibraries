/*
Eulerグラフ判定アルゴリズム Euler Detection Algorithm
無向連結グラフがEulerグラフ(一筆書き可能なグラフ)であるかを判定する.
Input:
    links: links[u]が頂点uと隣接した頂点のvectorであるような2次元vector.
Output:
    (bool): Eulerグラフであればtrue, そうでなければfalse.
*/

#include <vector>
using namespace std;

bool isEulerian(vector<vector<int> >& links) {
    int odd = 0;
    for (int v = 0; v < int(links.size()); v++) {
        if (int(links[v].size()) % 2) return false;
    }
    return true;
}

bool isSemiEulerian(vector<vector<int> >& links) {
    int odd = 0;
    for (int v = 0; v < int(links.size()); v++) {
        odd += int(links[v].size()) % 2;
        if (odd > 2) return false;
    }
    return odd == 2;
}

/*
Eulerグラフ判定アルゴリズム Euler Detection Algorithm
有向連結グラフがEulerグラフ(一筆書き可能なグラフ)であるかを判定する.
Input:
    links: links[u]が頂点uから1回の移動で到達可能な頂点のvectorであるような2次元vector.
    rev_links: links[u]が頂点uへ1回の移動で到達可能な頂点のvectorであるような2次元vector.
Output:
    (bool): Eulerグラフであればtrue, そうでなければfalse.
*/

bool isEulerian(vector<vector<int> > &links,
    vector<vector<int> >& rev_links) {
    int odd = 0;
    for (int v = 0; v < int(links.size()); v++) {
        if (links[v].size() != rev_links[v].size()) return false;
    }
    return true;
}

bool isSemiEulerian(vector<vector<int> >& links,
    vector<vector<int> >& rev_links) {
    int g = 0, l = 0;
    for (int v = 0; v < int(links.size()); v++) {
        if (links[v].size()+1 == rev_links[v].size()) g++;
        else if (links[v].size()-1 == rev_links[v].size()) l++;
        else if (links[v].size() != rev_links[v].size()) return false;
    }
    return g == 1 && l == 1;
}
