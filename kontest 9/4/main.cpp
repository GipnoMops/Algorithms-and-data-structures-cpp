#include <iostream>
#include <vector>
#include <algorithm>

int F (int a) {
    return a & (a + 1);
}

int pref_sum (int r, std::vector<int>& t) {
    int sum = 0;
    while (r >= 0) {
        sum += t[r];
        r = F(r) - 1;
    }
    return sum;
}

int segment_sum (int l, int r, std::vector<int>& t) {
    if (l == 0)
        return pref_sum(r, t);
    return pref_sum(r, t) - pref_sum(l - 1, t);
}

int bin_search_min (int key, int l, int r, std::vector<int>& t) {
    int midd = 0;
    int fix;
    if (l == -1) {
        fix = 0;
        l = 0;
    } else {
        fix = pref_sum(l, t);
    }

    while (true) {
        midd = (l + r) / 2;
        int value = pref_sum(midd, t) - fix;
        if (key < value)
            r = midd - 1;
        else if (key > value)
            l = midd + 1;
        else {
            while ((pref_sum(midd, t) - fix) != key - 1) {
                --midd;
            }
            return ++midd;
        }


        if (l > r)
            return -1;
    }
}

/*int bin_search_max (int key, std::vector<int>& t) {
    int midd = 0,  l = 0, r = t.size() - 1;
    while (true) {
        midd = (l + r) / 2;
        int value = pref_sum(midd, t);
        if (key < value)
            r = midd - 1;
        else if (key > value)
            l = midd + 1;
        else if (key != t.size()){
            while (pref_sum(midd, t) != key + 1) {
                ++midd;
            }
            return --midd;
        } else
            return midd;


        if (l > r)
            return -1;
    }
}*/

void k_even (int k, int l , int r, std::vector<int>& a, std::vector<int>& t) {
    int pref_k;
    pref_k = bin_search_min(k, l - 1, r, t);

    if (pref_k == -1)
        std::cout << "NONE\n";
    else
        std::cout << a[pref_k] << "\n";
}

void inc(int i, int delta, bool flag, std::vector<int>& t) {
    if (delta % 2 == 0) return;
    if (!flag) {
        while (i < t.size()) {
            ++t[i];
            i = i | (i + 1);
        }
    } else {
        while (i < t.size()) {
            --t[i];
            i = i | (i + 1);
        }
    }
}


int main() {
    int n;
    std::cin >> n;
    std::vector<int> a;
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        a.push_back(value);
    }

    std::vector<int> t(n, 0);
    for (int i = 0; i < n; ++i) {
        for (int k = F(i); k <= i; ++k)
            t[i] += abs(a[k] + 1) % 2;
    }

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int operation;
        std::cin >> operation;
        if (operation == 1) {
            int l, r, k;
            std::cin >> l >> r >> k;
            k_even(k, l ,r, a, t);
        } else {
            int k, x;
            std::cin >> k >> x;
            inc(k, x - a[k], abs(a[k]) % 2 == 0, t);
            a[k] = x;
        }
    }
    return 0;
}
