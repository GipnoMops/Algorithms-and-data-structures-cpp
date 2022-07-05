#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
using ll = long long;

const int INF = (int)1e9+7, mod = (int)1e9+9, pw = 31, N = (int)1e5+123, M = (int)1e6+123;
const double eps = 1e-11;
const long long inf = 1e18;

struct node{
    ll sum, add;
    int l, r;
}t[4 * N];

int n;

void push(int v){
    if(t[v].add){
        t[v].sum += 1ll * (t[v].r - t[v].l + 1) * t[v].add;
        if(t[v].l < t[v].r){
            t[v+v].add += t[v].add;
            t[v+v+1].add += t[v].add;
        }
        t[v].add = 0;
    }
}
void build(vector<int>& a, int v = 1, int tl = 1, int tr = n){
    t[v].l = tl;
    t[v].r = tr;
    if(tl == tr){
        t[v].sum = a[tl];
    }
    else{
        int mid = (tl + tr) / 2;
        build(a, v+v, tl, mid);
        build(a, v+v+1, mid+1, tr);
        t[v].sum = t[v+v].sum + t[v+v+1].sum;
    }
}

ll get(int l, int r, int v = 1, int tl = 1, int tr = n){
    push(v);
    if(max(l, tl) > min(r, tr)) return 0;
    if(l <= tl && tr <= r) return t[v].sum;
    int mid = (tl + tr) / 2;
    return get(l, r, v+v, tl, mid) + get(l, r, v+v+1, mid+1, tr);
}

void upd(int l, int r, ll x, int v = 1, int tl = 1, int tr = n){
    push(v);
    if(max(l, tl) > min(r, tr)) return;
    if(l <= tl && tr <= r){
        t[v].add += x;
        push(v);
        return;
    }
    int mid = (tl + tr) / 2;
    upd(l, r, x, v+v, tl, mid);
    upd(l, r, x, v+v+1, mid+1, tr);
    t[v].sum = t[v+v].sum + t[v+v+1].sum;
}
int main () {
    int n;
    cin >> n;
    vector<int> vec;
    for (int i = 0; i < n; ++i) {
        int elem;
        cin >> elem;
        vec.push_back(elem);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int T;
        cin >> T;
        if (T == 1) {
            int l, r;
            cin >> l >> r;
            cout << get(l, r);
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            upd(l, r, x);
        }
    }
    return 0;
}