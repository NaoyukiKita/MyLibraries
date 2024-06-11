/*
Union-Find木 Union-Find tree
*Constructor*
    Input:
        size: 配列のサイズ
    Output: *instance*
unite
    Input:
        x, y: 連結対象のindex
    Output: Null
hasSameRoot
    Input:
        x, y: 判定対象のindex
    Output:
        (bool): x, yが同じ集合に属していたらtrue, そうでなければfalse
*/
#include <vector>
using namespace std;

class UnionFind {
private:
    int size;
    vector<int> root;
    
    int _root(int x) {
        if (root[x] == -1) return x;
        return root[x] = _root(root[x]);
    }

public:
    UnionFind(int size) {
        this->size = size;
        this->root = vector<int>(size, -1);
    }
    
    void unite(int x, int y) {
        int root_x = _root(x);
        int root_y = _root(y);
        
        if (root_x == root_y) return;
        
        root[root_x] = root_y;
    }
    
    bool hasSameRoot(int x, int y) {
        return _root(x) == _root(y);
    }
};