/*
numpy.argsortと同じ
Input:
    vec: 対象のベクトル. これ自身はソートされない.
    indices: 返却値を格納するvector. 要素数=vecの要素数
Output: Null
*/

#include <vector>
#include <algorithm>
using namespace std;

void argsort(vector<int>& vec, vector<int>& indices) {
    vector<pair<int, int> > vec2(vec.size());
    for (int i = 0; i < vec.size(); i++) {
        vec2[i] = make_pair(vec[i], i);
    }
    sort(vec2.begin(), vec2.end());
    for (int i = 0; i < vec.size(); i++) {
        indices[i] = vec2[i].second;
    }
}
