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

    std::vector<std::pair<int, int>> max_pow;
    int pow = 0;
    int pow_value = 1;
    max_pow.emplace_back(0, 0);
    for (int i = 1; i <= n; ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2;
            ++pow;
        }
        max_pow.emplace_back(pow, pow_value);
    }

    std::vector<std::vector<int>> pref(pow + 1, std::vector<int>(n));
    pref[0] = sequence;
    pow_value = 1;
    for (int i = 1; i <= pow; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j + pow_value < n) {
                pref[i][j] = std::max(pref[i - 1][j], pref[i - 1][j + pow_value]);
            } else break;
        }
        pow_value *= 2;
    }


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

        int k, value_of_k;
        k = max_pow[r - l + 1].first;
        value_of_k = max_pow[r - l + 1].second;
        answer = (answer + std::max(pref[k][l], pref[k][r - value_of_k + 1])) % 1000000007;
    }
    std::cout << answer << "\n";
    return 0;
}

/*
 * 1 2 3 4 5
 * 2 3 4
 * 4 5
 */