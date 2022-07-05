#include <iostream>
#include <vector>

using namespace std;
using pii = pair<int, int>;
using ll = long long;

const int INF = (int)1e9+7, mod = (int)1e9+9, pw = 31, N = (int)1e5+123, M = (int)1e6+123;
const double eps = 1e-11;
const long long inf = 1e18;

struct node{
    ll sum, add;
    int l, r;
};


void push(int v, vector<node>& t){
    if(t[v].add){
        t[v].sum += 1ll * (t[v].r - t[v].l + 1) * t[v].add;
        if(t[v].l < t[v].r){
            t[v+v].add += t[v].add;
            t[v+v+1].add += t[v].add;
        }
        t[v].add = 0;
    }
}
void build(vector<int>& a, int tr, vector<node>& t, int v = 1, int tl = 1){
    t[v].l = tl;
    t[v].r = tr;
    if(tl == tr){
        t[v].sum = a[tl];
    }
    else{
        int mid = (tl + tr) / 2;
        build(a, v+v, t, tl, mid);
        build(a, v+v+1, t, mid+1, tr);
        t[v].sum = t[v+v].sum + t[v+v+1].sum;
    }
}

ll get(int l, int r, int tr, vector<node>& t, int v = 1, int tl = 1){
    push(v, t);
    if(max(l, tl) > min(r, tr)) return 0;
    if(l <= tl && tr <= r) return t[v].sum;
    int mid = (tl + tr) / 2;
    return get(l, r, v+v, t, tl, mid) + get(l, r, v+v+1, t, mid+1, tr);
}

void upd(int l, int r, ll x, int tr, vector<node>& t, int v = 1, int tl = 1){
    push(v, t);
    if(max(l, tl) > min(r, tr)) return;
    if(l <= tl && tr <= r){
        t[v].add += x;
        push(v, t);
        return;
    }
    int mid = (tl + tr) / 2;
    upd(l, r, x, v+v, t, tl, mid);
    upd(l, r, x, v+v+1, t, mid+1, tr);
    t[v].sum = t[v+v].sum + t[v+v+1].sum;
}

int main () {
    int n;
    cin >> n;
    vector<int> vec;
    vector<node> t;
    for (int i = 0; i < n; ++i) {
        int elem;
        cin >> elem;
        vec.push_back(elem);
    }
    build(vec, n, t);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int T;
        cin >> T;
        if (T == 1) {
            int l, r;
            cin >> l >> r;
            cout << get(l, r, vec.size(), t);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            upd(l, r, x, vec.size(), t);
        }
    }
    return 0;
}