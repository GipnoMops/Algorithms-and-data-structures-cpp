#include <iostream>
#include <vector>

int F (int a) {
    return a & (a + 1);
}

long long int pref_sum (int r, std::vector<long long int>& t) {
    long long int sum = 0;
    while (r >= 0) {
        sum += t[r];
        r = F(r) - 1;
    }
    return sum;
}

long long int segment_sum (int l, int r, std::vector<long long int>& t) {
    if (l == 0)
        return pref_sum(r, t);
    return pref_sum(r, t) - pref_sum(l - 1, t);
}

void inc(int i, int delta, std::vector<long long int>& t) {
    while (i < t.size()) {
        t[i] += delta;
        i = i | (i + 1);
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

    std::vector<long long int> t(n, 0);
    for (int i = 0; i < n; ++i)
        inc(i, a[i], t);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int operation;
        std::cin >> operation;
        if (operation == 1) {
            int l, r;
            std::cin >> l >> r;
            std::cout << segment_sum(l, r, t) << "\n";
        } else {
            int k, x;
            std::cin >> k >> x;
            inc(k, x - a[k], t);
            a[k] = x;
        }
    }
    return 0;
}
