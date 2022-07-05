#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <memory.h>
#include <complex>

using namespace std;

const int mod = 786433;

typedef complex<long double> dou_cpx;

void fft(vector<dou_cpx> &a, bool invert) {
    int n = (int)a.size();
    if (n == 1) return;
    vector<dou_cpx> a0(n/2); vector<dou_cpx> a1(n/2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }
    fft (a0, invert); fft (a1, invert);
    long double ang = 2 * M_PI / n * (invert ? -1 : 1);
    dou_cpx w (1),  wn (cos(ang), sin(ang));
    for (int i = 0; i < n / 2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

void multiply(const vector<int> & a, const vector<int> & b, vector<int> & res) {
    vector<dou_cpx> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa, false); fft(fb, false);
    for (size_t i = 0; i < n; ++i) fa[i] *= fb[i];
    fft(fa, true);
    res.resize(n);
    for (size_t i = 0; i < n; ++i) {
        long long x = (long long)(fa[i].real() + 0.5);
        x %= (long long)mod;
        res[i] = (int)x;
    }
//
//    size_t res_size = min(n, MAX_PRICE);
//    res.resize(res_size);
//    for (size_t i=0; i < res_size; ++i) {
//        long long x = (long long)(fa[i].real() + 0.5);
//        x %= (long long)mod;
//        res[i] = (int)x;
//    }
}

void binpow(std::vector<int>& a, int k, std::vector<int>& result) {
    while (k) {
        if (k & 1) {
            multiply(result, a, result);
        }
        multiply(a, a, a);
        k >>= 1;
    }
}


int main() {
    int n, k, q;
    std::cin >> n >> k >> q;
    std::vector<int> a(65536);
    for (int i = 0; i < n; ++i) {
        int x; std::cin >> x;
        ++a[x];
    }

    vector<int> result = a;

    binpow(ways, k - 1, result);

    std::vector<int> pref_sum = {0};
    for (int x : result) {
        pref_sum.push_back((pref_sum.back() + x) % mod);
    }

    for (long long i = 0; i < q; ++i) {
        long long l, r;
        std::cin >> l >> r;
        std::cout << (pref_sum[std::min(r + 1, (long long)pref_sum.size() - 1)] - pref_sum[l] + mod) % mod << "\n";
    }
    return 0;
}