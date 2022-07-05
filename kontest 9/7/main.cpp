#include <iostream>
#include <vector>
#include <algorithm>

const long int INF = 1000000099;


void build (std::vector<std::vector<int>>& t, std::vector<int>& a, int v, int tl, int tr) {
	if (tl == tr)
		t[v] = std::vector<int> (1, a[tl]);
	else {
		int tm = (tl + tr) / 2;
		build (t, a, v * 2, tl, tm);
		build (t, a, v * 2 + 1, tm + 1, tr);
		std::merge (t[v * 2].begin(), t[v * 2].end(), t[v * 2 + 1].begin(), t[v * 2 + 1].end(),
			back_inserter (t[v]));
	}
}

int query (std::vector<std::vector<int>>& t, int v, int tl, int tr, int l, int r, int x) {
    if (l > r)
        return INF;
    if (l == tl && tr == r) {
        std::vector<int>::iterator pos = std::lower_bound(t[v].begin(), t[v].end(), x);
        if (pos != t[v].end())
            return *pos;
        return INF;
    }
    int tm = (tl + tr) / 2;
    return std::min (
            query (t, v * 2, tl, tm, l, std::min(r, tm), x),
            query (t, v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, x)
    );
}

int main () {
    int n;
    std::cin >> n;
    std::vector<int> vec;

    int t_size = 2;
    while (t_size < n)
        t_size *= t_size;

    std::vector<std::vector<int>> t(2 * t_size);
    for (int i = 0; i < n; ++i) {
        int elem;
        std::cin >> elem;
        vec.push_back(elem);
    }
    build(t, vec, 1, 0, n - 1);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r, x;
        std::cin >> l >> r >> x;
        int value = query(t, 1, 0, n - 1, l, r, x + 1);
        if (value != INF)
            std::cout << value << "\n";
        else
            std::cout << "NONE\n";
    }
    return 0;
}