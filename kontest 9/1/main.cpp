#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> sequence;
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        sequence.push_back(value);
    }

    std::vector<long long int> pref(n);
    pref[0] = sequence[0];
    for (int i = 1; i < n; ++i)
        pref[i] = pref[i - 1] + sequence[i];


    long long int q, x_0;
    std::cin >> q >> x_0;
    long long int x_1, x_2, answer = 0;
    for (int i = 0; i < q; ++i) {
        if (i == 0)
            x_1 = x_0;
        else
            x_1 = (11173 * x_2 + 1) % 1000000007;

        x_2 = (11173 * x_1 + 1) % 1000000007;

        int l, r;
        l = std::min(x_1 % n, x_2 % n);
        r = std::max(x_1 % n, x_2 % n);

        if (l == 0)
            answer = (answer + pref[r]) % 1000000007;
        else
            answer = (answer + pref[r] - pref[l - 1]) % 1000000007;
    }
    std::cout << answer << "\n";
    return 0;
}
