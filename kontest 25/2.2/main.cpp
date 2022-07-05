#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <cassert>

const int MOD = 786433;

typedef std::complex<double> dou_cpx;

void fft2 (std::vector<dou_cpx>& a, bool invert) {
    int n = (int) a.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap (a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * M_PI / len * (invert ? -1 : 1);
        dou_cpx wlen (cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            dou_cpx w (1);
            for (int j = 0; j < len / 2; ++j) {
                dou_cpx u = a[i + j],  v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) for (int i = 0; i < n; ++i) a[i] /= n;
}

std::vector<int> multiply(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<dou_cpx> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < std::max(a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);

    fft2 (fa, false),  fft2 (fb, false);
    for (size_t i = 0; i < n; ++i) fa[i] = (fa[i] * fb[i]);
    fft2 (fa, true);

    std::vector<int> res(n);
    for (size_t i = 0; i < n; ++i) res[i] = int (fa[i].real() + 0.5);

    int carry = 0;
    for (size_t i = 0; i < n; ++i) {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }

    while (!res.empty() && res.back() == 0) res.pop_back();
    if (res.empty()) res = {0};
    return res;
}

std::vector<int> binpow (std::vector<int>& a, int n) {
    std::vector<int> res{1};
    while (n) {
        if (n & 1) res = multiply(res, a);
        a = multiply(a, a);
        n >>= 1;
    }
    return res;
}


int main() {
    int n, k, q;
    std::cin >> n >> k >> q;

    std::vector<int> a(65536);
    for (int i = 0; i < n; ++i) {
        int x; std::cin >> x;
        ++a[x];
    }

    std::vector<int> res = binpow(a, k);

    std::vector<int> pref_sum = {0};
    for (int x : res) pref_sum.push_back((pref_sum.back() + x) % MOD);

    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        std::cout << (pref_sum[std::min(r + 1, (int)pref_sum.size() - 1)] - pref_sum[l] + MOD) % MOD << "\n";
    }
    return 0;
}
