#include <iostream>
#include <cmath>
#include <map>

std::pair<std::map<int, int>, std::pair<int, int>> factorize(int x) {
    std::map<int, int> factors;
    int max_pow = 0, elem = 0;

    for (int i = 2; i <= sqrt(x); i++) {
        while (x % i == 0) {
            factors[i]++;
            if (max_pow < factors[i]) {
                max_pow = factors[i];
                elem = i;
            }
            x /= i;
        }
    }

    if (x != 1) factors[x]++;

    if (max_pow < factors[x]) {
        max_pow = factors[x];
        elem = x;
    }

    return std::make_pair(factors, std::make_pair(max_pow, elem));
}

int main() {
    long long int a, anwer = 1;
    std::cin >> a;
    auto factors = factorize(a);
    for (auto [elem, pow] : factors.first) anwer *= elem;

    int max_pow = factors.second.first, elem = factors.second.second;
    while (anwer < max_pow) {
        anwer *= elem;
        max_pow = (max_pow + 1) / 2;
    }
    std::cout << anwer << "\n";
    return 0;
}
