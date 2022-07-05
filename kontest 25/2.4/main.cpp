#include <vector>
#include <iostream>

const long long MOD = 786433;
const long long mod = 786433;
const long long root = 25;
const long long root_1 = 94372;
const long long root_pw = 1<<17;

long long binpow(long long a, long long b) {
    long long res = 1;
    for (; b; b >>= 1) {
        if (b & 1)
            res = (1LL * res * a) % mod;
        a = (1LL * a * a) % mod;
    }
    return res;
}

//long long binpow (long long long long a, long long n) {
//    long long long long res = 1;
//    while (n) {
//        if (n & 1)
//            res = (res * a) % mod;
//        a = (a * a) % mod;
//        n >>= 1;
//        std::cout << "binpow = " << res << "\n";
//    }
//    return (res % mod);
//}

long long reverse(const long long& a) {
    return binpow(a,  mod - 2);
}


void fft (std::vector<long long>& a, bool invert) {
	long long n = (long long) a.size();
 
	for (long long i = 1, j = 0; i < n; ++i) {
		long long bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			std::swap (a[i], a[j]);
	}
 
	for (long long len = 2; len <= n; len <<= 1) {
		long long wlen = invert ? root_1 : root;
		for (long long i = len; i < root_pw; i <<= 1)
			wlen = int (wlen * 1ll * wlen % mod);
		for (long long i = 0; i < n; i += len) {
			long long w = 1;
			for (long long j = 0; j < len / 2; ++j) {
				long long u = a[i + j],  v = int (a[i + j + len / 2] * 1ll * w % mod);
				a[i + j] = u + v < mod ? u + v : u + v - mod;
				a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
				w = int (w * 1ll * wlen % mod);
			}
		}
	}
	if (invert) {
		long long nrev = reverse(n);
		for (long long i = 0; i < n; ++i)
			a[i] = int (a[i] * 1ll * nrev % mod);
	}
}

std::vector<long long> multiply(const std::vector<long long>& a, const std::vector<long long>& b) {
    std::vector<long long> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < std::max(a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);

    fft(fa, false),  fft(fb, false);
    for (size_t i = 0; i < n; ++i) fa[i] = (1ll * fa[i] * fb[i]) % mod;
    fft(fa, true);

    std::vector<long long> res(n);
    for (size_t i = 0; i < n; ++i) res[i] = fa[i];

    long long carry = 0;
    for (size_t i = 0; i < n; ++i) {
        res[i] += carry;
        carry = res[i] / 10;
        res[i] %= 10;
    }

    while (!res.empty() && res.back() == 0) res.pop_back();
    if (res.empty()) res = {0};
    return res;
}

std::vector<long long> binpow (std::vector<long long>& a, long long n) {
    std::vector<long long> res{1};
    while (n) {
        if (n & 1) res = multiply(res, a);
        a = multiply(a, a);
        n >>= 1;
    }
    return res;
}


int main() {
    std::string s1, s2;
    std::vector<long long> a, b;
    bool a_flag = true, b_flag = true;
    getline(std::cin, s1);
    getline(std::cin, s2);
    if (s1[0] == '-') a_flag = false; if (s2[0] == '-') b_flag = false;

    if (a_flag) for (auto elem : s1) a.push_back(elem - '0');
    else for (long long i = 1; i < s1.size(); ++i) a.push_back(s1[i] - '0');

    if (b_flag) for (auto elem : s2) b.push_back(elem - '0');
    else for (long long i = 1; i < s2.size(); ++i) b.push_back(s2[i] - '0');

    std::reverse(a.begin(), a.end());
    std::reverse(b.begin(), b.end());
    auto answer = multiply(a, b);
    std::reverse(answer.begin(), answer.end());
    if (answer.empty()) std::cout << 0;
    else {
        if (a_flag + b_flag == 1) std::cout << '-';
        for (long long i : answer) std::cout << i;
    }
    return 0;
}



int main() {
    long long n, k, q;
    std::cin >> n >> k >> q;

    std::vector<long long> a(65536);
    for (long long i = 0; i < n; ++i) {
        long long x; std::cin >> x;
        ++a[x];
    }

    std::vector<long long> res = binpow(a, k);

    std::vector<long long> pref_sum = {0};
    for (long long x : res) {
        std::cout << x << " ";
        pref_sum.push_back((pref_sum.back() + x) % MOD);
    }
    std::cout << "\n";

    for (long long i = 0; i < q; ++i) {
        long long l, r;
        std::cin >> l >> r;
        std::cout << (pref_sum[std::min(r + 1, (long long)pref_sum.size() - 1)] - pref_sum[l] + MOD) % MOD << "\n";
    }
    return 0;
}
