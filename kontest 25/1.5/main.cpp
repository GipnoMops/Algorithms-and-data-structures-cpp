#include <iostream>
#include <complex>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>


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
    if (invert)
        for (int i = 0; i < n; ++i)
            a[i] /= n;
}

void fft(std::vector<dou_cpx>& a, bool invert) {
    int n = (int) a.size();
    if (n == 1)  return;

    std::vector<dou_cpx> a0(n/2),  a1(n/2);
    for (int i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }
    fft (a0, invert); fft (a1, invert);

    double ang = 2 * M_PI/n * (invert ? -1 : 1);
    dou_cpx w(1),  wn(cos(ang), sin(ang));
    for (int i = 0; i < n/2; ++i) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) a[i] /= 2,  a[i + n/2] /= 2;
        w *= wn;
    }
}

std::vector<int> multiply(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<dou_cpx> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < std::max(a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);

    fft2 (fa, false),  fft2 (fb, false);
    for (size_t i = 0; i < n; ++i) fa[i] *= fb[i];
    fft2 (fa, true);

    std::vector<int> res(n);
    for (size_t i = 0; i < n; ++i) res[i] = int (fa[i].real() + 0.5);

    int carry = 0;
    for (size_t i = 0; i < n; ++i) {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }

    while (!res.empty() && res[res.size() - 1] == 0) res.pop_back();
    return res;
}

int main() {
    std::string s1, s2;
    std::vector<int> a, b;
    bool a_flag = true, b_flag = true;
    getline(std::cin, s1);
    getline(std::cin, s2);
    if (s1[0] == '-') a_flag = false; if (s2[0] == '-') b_flag = false;

    if (a_flag) for (auto elem : s1) a.push_back(elem - '0');
    else for (int i = 1; i < s1.size(); ++i) a.push_back(s1[i] - '0');

    if (b_flag) for (auto elem : s2) b.push_back(elem - '0');
    else for (int i = 1; i < s2.size(); ++i) b.push_back(s2[i] - '0');

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    auto answer = multiply(a, b);
    std::reverse(answer.begin(), answer.end());
    if (answer.empty()) std::cout << 0;
    else {
        if (a_flag + b_flag == 1) std::cout << '-';
        for (int i : answer) std::cout << i;
    }
    return 0;
}
