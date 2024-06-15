#include <iostream>
#include <vector>
#include <functional>
using namespace std;
using ll = long long int;

// update
auto add = [](ll a, ll b) { return a+b; };
auto set = [](ll a, ll b) { return b; };

// query
auto q_sum = [](ll a, ll b) { return a+b; };
auto q_max = [](ll a, ll b) { return a>b ? a:b; };
auto q_min = [](ll a, ll b) { return a<b ? a:b; };

// lazy
auto l_sum = [](ll a, int left, int right) { return a*(right-left); };
auto l_max = [](ll a, int left, int right) { return a; };
auto l_min = [](ll a, int left, int right) { return a; };

// resolve
auto r_sum = [](ll a) { return a/2; };
auto r_max = [](ll a) { return a; };
auto r_min = [](ll a) { return a; };

class SegTree {
public:
    const ll INFTY = 9223372036854775807;
    int size, capacity;
    vector<ll> vec, lazy;
    function<ll (ll,ll)> _update, _query;
    function<ll (ll, int, int)> _lazy;
    function<ll (ll)> _resolve;

    int _parent(int index) { return (index - 1) >> 1; }
    int _leftChild(int index) { return (index << 1) + 1; }
    int _rightChild(int index) { return (index << 1) + 2; }
    int _isLeaf(int index) { return index >= capacity-1; }

    void _rangeUpdate(int begin, int end, int value,
                int index, int left, int right) {
        if (begin == end) return;
        if (begin == right || end == left) return;

        if (begin == left && end == right) {
            if (_isLeaf(index)) {
                vec[index] = _update(vec[index], value);
            } else {
                if (lazy[index] == INFTY) lazy[index] = _lazy(value, left, right);
                else {
                    lazy[index] = _update(lazy[index], _lazy(value, left, right));
                }
                vec[index] = _update(vec[index], _lazy(value, left, right));
            }
            return;
        }

        if (left <= begin && end <= right) {
            // 1step lazy-propagation
            int lchild = _leftChild(index), rchild = _rightChild(index);

            if (lazy[index] != INFTY) {
                vec[lchild] = _update(vec[lchild], _resolve(lazy[index]));
                vec[rchild] = _update(vec[rchild], _resolve(lazy[index]));
                if (!_isLeaf(lchild)) {
                    lazy[lchild] = _update(lazy[lchild], _resolve(lazy[index]));
                    lazy[rchild] = _update(lazy[rchild], _resolve(lazy[index]));
                }
                lazy[index] = INFTY;
            }

            int mid = (left+right) / 2;
            if (begin < mid) {
                _rangeUpdate(begin, min(end, mid), value, lchild, left, mid);
            }
            if (mid < end) {
                _rangeUpdate(max(begin, mid), end, value, rchild, mid, right);
            }
            vec[index] = _query(vec[lchild], vec[rchild]);
            return;
        }
        cout << "Unexpected condition rangeUpdate\n";
        return;
    }
    
    ll _rangeQuery(int begin, int end, int index, int left, int right) {
        if (begin == end) return INFTY;
        if (begin == right || end == left) return INFTY;
        
        if (begin == left && end == right) return vec[index];
        
        if (left <= begin && end <= right) {
            int lchild = _leftChild(index), rchild = _rightChild(index);
            
            if (lazy[index] != INFTY) {
                vec[lchild] = _update(vec[lchild], _resolve(lazy[index]));
                vec[rchild] = _update(vec[rchild], _resolve(lazy[index]));
                if (!_isLeaf(lchild)) {
                    lazy[lchild] = _update(lazy[lchild], _resolve(lazy[index]));
                    lazy[rchild] = _update(lazy[rchild], _resolve(lazy[index]));
                }
                lazy[index] = INFTY;
            }
            
            int mid = (left+right) / 2;
            ll lres = INFTY, rres = INFTY;
            if (begin < mid) {
                lres = _rangeQuery(begin, min(end, mid), lchild, left, mid);
            }
            if (mid < end) {
                rres = _rangeQuery(max(begin, mid), end, rchild, mid, right);
            }
            
            if (lres != INFTY && rres != INFTY) return _query(lres, rres);
            return lres != INFTY ? lres : rres;
        }
        cout << "Unexpected condition rangeQuery ";
        cout <<  begin << " " << end << " " << index << " " << left << " " << right << endl;
        return INFTY;
    }

    SegTree(int size,
                function<ll (ll,ll)> _update,
                function<ll (ll,ll)> _query,
                function<ll (ll, int, int)> _lazy,
                function<ll (ll)> _resolve)
        : size(size), _update(_update), _query(_query),
            _lazy(_lazy), _resolve(_resolve) {
        for (capacity = 1; capacity < size; capacity <<= 1);
        vec = vector<ll>((capacity << 1) - 1);
        lazy = vector<ll>(capacity-1, INFTY);
    }

    SegTree(vector<int> initial,
                function<ll (ll,ll)> _update,
                function<ll (ll,ll)> _query,
                function<ll (ll, int, int)> _lazy,
                function<ll (ll)> _resolve)
        : size(initial.size()), _update(_update), _query(_query),
            _lazy(_lazy), _resolve(_resolve) {
        for (capacity = 1; capacity < size; capacity <<= 1);
        vec = vector<ll>((capacity << 1) - 1);
        lazy = vector<ll>(capacity-1, INFTY);
        copy(initial.begin(), initial.end(), vec.begin()+capacity-1);
        for (int parent = capacity-2; parent >= 0; parent--) {
            vec[parent] = _query(vec[_leftChild(parent)],
                                    vec[_rightChild(parent)]);
        }
    }

    void rangeUpdate(int begin, int end, int value) {
        _rangeUpdate(begin, end, value, 0, 0, capacity);
    }
    
    ll rangeQuery(int begin, int end) {
        return _rangeQuery(begin, end, 0, 0, capacity);
    }

    void show() {
        int cur = 2;
        for (int node = 0; node < vec.size(); node++) {
            cout << vec[node];
            if (!_isLeaf(node)) {
                if (lazy[node] == INFTY) cout << "(-)";
                else cout << "(" << lazy[node] << ")";
            }
            if (node == cur-2) {
                cout << "\n"; cur <<= 1;
            } else cout << " ";
        }
    }
};