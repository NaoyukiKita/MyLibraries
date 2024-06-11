/*
フェニック木, またはBIT Fenwick / Binary Indexed Tree
*Constructor*
    Input:
        size: 配列のサイズ
    Output: *instance*
*Constructor*
    Input:
        init_vec: 配列の初期状態
    Output: *instance*
add
    Input:
        index: 加算対象のインデックス
        amount: 加算量
    Output: Null
rangeAdd
    Input:
        begin: 加算区間の最小インデックス
        end: 加算区間の最大インデックス+1
        amount: 加算量
    Output: Null
rangeSum
    Input:
        begin: 総和区間の最小インデックス
        end: 総和区間の最大インデックス+1
    Output:
        sum: 区間和
access:
    Input:
        index: インデックス
    Output:
        value: 対象の値
*/

#include <iostream>
#include <vector>
using namespace std;
using ll = long long int;

class BIT {
private:
    int size, capacity;
    vector<ll> vec, pend;

    int _parent(int index) {return (index - 1) >> 1;}
    int _leftChild(int index) {return (index << 1) + 1;}
    int _rightChild(int index) {return (index << 1) + 2;}
    int _isLeaf(int index) {return index >= capacity-1;}

    void _rangeAdd(int begin, int end, ll amount,
            int index, int left, int right) {
        // [begin, end) is empty
        if (begin == end) return;
        // [begin, end) \cap [left, right) is empty
        if (begin == right || end == left) return;

        if (begin == left && end == right) {
            if (end-begin == 1) vec[index] += amount;
            else pend[index] += amount;
            return;
        }

        if (left <= begin && end <= right) {
            if (begin < (left+right)/2) {
                _rangeAdd(begin, min(end, (left+right)/2), amount,
                    _leftChild(index), left, (left+right)/2);
            }
            if ((left+right)/2 < end) {
                _rangeAdd(max(begin, (left+right)/2), end, amount,
                    _rightChild(index), (left+right)/2, right);
            }

            vec[index] += amount * (end-begin);
            return;
        }

        cout << "Unexpected condition occured!\n";
        return;
    }

    ll _rangeSum(int begin, int end,
            int index, int left, int right) {
        // [begin, end) is empty
        if (begin == end) return 0;
        // [begin, end) \cap [left, right) is empty
        if (begin == right || end == left) return 0;

        if (begin == left && end == right) {
            if (_isLeaf(index)) return vec[index];
            else return vec[index] + pend[index]*(right-left);
        }
        
        if (left <= begin && end <= right) {
            // 1step lazy-propagation
            vec[index] += pend[index] * (right-left);
            if (_isLeaf(_leftChild(index))) {
                vec[_leftChild(index)] += pend[index];
                vec[_rightChild(index)] += pend[index];
            } else {
                pend[_leftChild(index)] += pend[index];
                pend[_rightChild(index)] += pend[index];
            } pend[index] = 0;
            
            ll res = 0;
            if (begin < (left+right)/2) {
                res += _rangeSum(begin, min(end, (left+right)/2),
                        _leftChild(index), left, (left+right)/2);
            }
            if ((left+right)/2 < end) {
                res += _rangeSum(max(begin, (left+right)/2), end,
                        _rightChild(index), (left+right)/2, right);
            }
            
            return res;
        }
        
        cout << "Unexpected condition occured!\n";
        return 0;
    }

public:
    BIT (int size) {
        this->size = size;
        for (capacity = 1; capacity < size; capacity <<= 1);
        vec = vector<ll>((capacity << 1) - 1);
        pend = vector<ll>(capacity - 1);
    }

    BIT(vector<ll>& init_vec) {
        size = init_vec.size();
        for (capacity = 1; capacity < size; capacity <<= 1);
        vec = vector<ll>((capacity << 1) - 1);
        pend = vector<ll>(capacity - 1);
        copy(init_vec.begin(), init_vec.end(), vec.begin()+capacity-1);
        // back-propagation
        for (int parent = capacity-2; parent >= 0; parent--) {
            vec[parent] = 
                vec[_leftChild(parent)]
                + vec[_rightChild(parent)];
        }
    }

    void rangeAdd(int begin, int end, ll amount) {
        _rangeAdd(begin, end, amount, 0, 0, capacity);
    }

    void add(int index, int amount) {
        int leaf = (capacity-1) + index;
        vec[leaf] += amount;
        // backpropagation
        for (int child = leaf; child != 0; child = _parent(child)) {
            vec[_parent(child)] += amount;
        }
    }
    
    ll rangeSum(int begin, int end) {
        return _rangeSum(begin, end, 0, 0, capacity);
    }
    
    ll access(int index) {
        int current = 0;
        int left = 0, right = capacity;
        while (left != index || right != index+1) {
            // 1step lazy-propagation
            vec[current] += pend[current] * (right-left);
            if (_isLeaf(_leftChild(index))) {
                vec[_leftChild(current)] += pend[current];
                vec[_rightChild(current)] += pend[current];
            } else {
                pend[_leftChild(current)] += pend[current];
                pend[_rightChild(current)] += pend[current];
            } pend[current] = 0;
            
            // update
            if (index < (left+right)/2) {
                right = (left+right)/2;
                current = _leftChild(current);
            } else {
                left = (left+right)/2;
                current = _rightChild(current);
            }
        }
        return vec[current];
    }
    
    void show() {
        int cur = 2;
        for (int node = 0; node < vec.size(); node++) {
            cout << vec[node];
            if (node < capacity-1) cout << "(" << pend[node] << ")";
            if (node == cur-2) {
                cout << "\n"; cur <<= 1;
            } else cout << " ";
        }
    }
};