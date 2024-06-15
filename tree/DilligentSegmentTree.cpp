/*
セグメント木(遅延評価なし) Segment Tree (no lazy propagation)
*Constructor*
    Input:
        size: 配列のサイズ
        _update: 更新則(setかadd)
        _query: クエリ(sumかmaxかmin)
    Output: *instance*
*Constructor*
    Input:
        init_vec: 配列の初期状態
        _update: 更新則(setかadd)
        _query: クエリ(sumかmaxかmin)
    Output: *instance*
update
    Input:
        index: 対象
        value: 更新量
    Output: Null
rangeQuery:
    Input:
        begin, end: 区間 [begin, end)
    Output:
        response: sumなら総和, maxなら最大値, minなら最小値
access:
    Input:
        index:
    Output:
        value: indexの値
*/

#include <iostream>
#include <functional>
#include <vector>
using namespace std;
using ll = long long int;

// update
auto add = [](ll a, ll b) { return a+b; };
auto set = [](ll a, ll b) { return b; };

// query
auto q_sum = [](ll a, ll b) { return a+b; };
auto q_max = [](ll a, ll b) { return a>b ? a:b; };
auto q_min = [](ll a, ll b) { return a<b ? a:b; };

class SegTree {
private:
    const ll INFTY = 9223372036854775807;
    int size, capacity;
    vector<ll> vec;
    function<ll (ll,ll)> _update, _query;

    int _parent(int index) { return (index - 1) >> 1; }
    int _leftChild(int index) { return (index << 1) + 1; }
    int _rightChild(int index) { return (index << 1) + 2; }
    int _isLeaf(int index) { return index >= capacity-1; }
    
    ll _rangeQuery(int begin, int end,
            int index, int left, int right) {
        if (begin == end) return INFTY;
        if (begin == right || end == left) return INFTY;
        
        if (begin == left && end == right) {
            return vec[index];
        }
        
        if (left <= begin && end <= right) {
            ll lres = INFTY, rres = INFTY;
            if (begin < (left+right)/2) {
                lres = _rangeQuery(begin, min(end, (left+right)/2),
                        _leftChild(index), left, (left+right)/2);
            }
            if ((left+right)/2 < end) {
                rres = _rangeQuery(max(begin, (left+right)/2), end,
                        _rightChild(index), (left+right)/2, right);
            }
            
            if (lres != INFTY && rres != INFTY) {
                return _query(lres, rres);
            }
            
            return lres == INFTY ? rres : lres;
        }
        
        cout << "Unexpected condition occured!\n";
        return 0;
    }

public:
    SegTree(int size, 
                function<ll (ll,ll)> _update,
                function<ll (ll,ll)> _query)
        : size(size), _update(_update), _query(_query) {
        for (capacity = 1; capacity < size; capacity <<= 1);
        vec = vector<ll>((capacity << 1) - 1);
    }
    
    SegTree(vector<ll> init_vec,
                function<ll (ll,ll)> _update,
                function<ll (ll,ll)> _query)
        : size(init_vec.size()), _update(_update), _query(_query) {
        for (capacity = 1; capacity < size; capacity <<= 1);
        vec = vector<ll>((capacity << 1) - 1);
        copy(init_vec.begin(), init_vec.end(), vec.begin()+capacity-1);
        // back
        for (int parent = capacity-2; parent >= 0; parent--) {
            vec[parent] = _query(vec[_leftChild(parent)],
                                vec[_rightChild(parent)]);
        }
    }
    
    void update(int index, int value) {
        if (index >= size) return;
        int leaf = (capacity-1) + index;
        vec[leaf] = _update(vec[leaf], value);
        if (leaf == 0) return;
        for (int parent = _parent(leaf);; parent = _parent(parent)) {
            vec[parent] = _query(vec[_leftChild(parent)],
                                vec[_rightChild(parent)]);
            if (parent == 0) break;
        }
    }
    
    ll rangeQuery(int begin, int end) {
        if (end > size) return 0;
        return _rangeQuery(begin, end, 0, 0, capacity);
    }
    
    ll access(int index) {
        if (index >= size) return 0;
        int leaf = (capacity-1) + index;
        return vec[leaf];
    }
    
    void show() {
        int cur = 2;
        for (int node = 0; node < vec.size(); node++) {
            cout << vec[node];
            if (node == cur-2) {
                cout << "\n"; cur <<= 1;
            } else cout << " ";
        }
    }
};