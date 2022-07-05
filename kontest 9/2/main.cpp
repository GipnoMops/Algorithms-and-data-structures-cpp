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

    std::vector<int> max_pow;
    int pow = 1;
    int pow_value = 1;
    for (int i = 1; i <= n; ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2;
            ++pow;
        }
        max_pow.push_back(pow_value);
    }

    std::vector<std::vector<int>> pref(pow, std::vector<int>(n));
    pref[0] = sequence;
    pow_value = 1;
    for (int i = 1; i < pow; ++i) {
        for (int j = 0; j < n; ++j) {
            pref[i][j] = std::max(pref[i - 1][j], pref[i - 1][j + pow_value]);
            std::cout << pref[i][j] << " ";
        }
        pow_value *= 2;
        std::cout << "\n";
    }


    /*long long int q, x_0;
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
            answer = (answer + std::max(pref[r], pref[l - 1]) % 1000000007;
    }
    std::cout << answer << "\n";*/
    return 0;
}
