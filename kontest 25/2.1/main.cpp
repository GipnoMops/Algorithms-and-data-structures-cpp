#include <iostream>
#include <vector>


using namespace std;
typedef long long ll;
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }


#define forn(i, n) for (int i = 0; i < (n); ++i)

namespace fft
{
    const int mod = 786433;
    const int base = 17;
    const int N = 1 << base;
    const int ROOT = 25;
    int root[N];
    int rev[N];

    void init()
    {
        forn(i, N) rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
        int NN = N >> 1;
        int z = 1;
        forn(i, NN)
        {
            root[i + NN] = z;
            z = z * (ll)ROOT % mod;
        }
        for (int i = NN - 1; i > 0; --i) root[i] = root[2 * i];
    }

    void fft(int *a, int *f)
    {
        forn(i, N) f[i] = a[rev[i]];
        for (int k = 1; k < N; k <<= 1) for (int i = 0; i < N; i += 2 * k) forn(j, k)
                {
                    int z = f[i + j + k] * (ll)root[j + k] % mod;
                    f[i + j + k] = (f[i + j] - z + mod) % mod;
                    f[i + j] = (f[i + j] + z) % mod;
                }
    }

    int A[N], B[N], C[N];
    int F[N], G[N];

    int pw(int a, int b) {
        int r = 1;
        for (; b; b >>= 1) {
            if (b & 1)
                r = (1LL*r*a) % mod;
            a = (1LL*a*a) % mod;
        }
        return r;
    }

    int inv(int x) {
        return pw(x, mod - 2);
    }

    void _mult(int eq)
    {
        fft(A, F);
        if (eq) forn(i, N) G[i] = F[i];
        else fft(B, G);
        int invN = inv(N);
        forn(i, N) A[i] = F[i] * (ll)G[i] % mod * invN % mod;
        reverse(A + 1, A + N);
        fft(A, C);
    }

    void mult(int n1, int n2, int eq = 0)
    {
        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;

        _mult(eq);

        //forn(i, n1 + n2) C[i] = 0;
        //forn(i, n1) forn(j, n2) C[i + j] = (C[i + j] + A[i] * (ll)B[j]) % mod;
    }
}

const int N = 50005;

vector < int > mul(vector < int > const& a, vector < int > const& b) {
    memcpy(fft::A, a.data(), sizeof(int)*N);
    memcpy(fft::B, b.data(), sizeof(int)*N);
    fft::mult(N, N);
    return vector < int > (fft::C, fft::C + N);
}

const int MOD = 786433;

int main() {
    int n, k, q;
    std::cin >> n >> k >> q;
    std::vector <int> a(N);
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        ++a[x];
    }

    vector <int> r(N);
    r[0] = 1;
    for (; k; k >>= 1) {
        if (k & 1)
            r = mul(r, a);
        a = mul(a, a);
    }

    vector < int > rs = {0};
    for (int x : r)
        rs.push_back((rs.back() + x) % MOD);

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << (rs[r+1] - rs[l] + MOD) % MOD << "\n";
    }

    return 0;
}
