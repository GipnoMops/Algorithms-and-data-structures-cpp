#include <iostream>
#include <vector>
#include <algorithm>
#include <future>


struct Request { int left; int right; };

std::vector<std::vector<int>> spar_tables(const std::vector<int>& num,
                                          std::vector<std::pair<int, int>>& max_pow,
                                          int pow, int l, int r) {

    std::vector<std::vector<int>> st(pow + 1, std::vector<int>(r - l));
    for (int i = l; i < r; ++i) st[0][i - l] = num[i];
    int pow_value = 1;
    for (int i = 1; i <= pow; ++i) {
        for (int j = 0; j < r - l; ++j) {
            if (j + pow_value < r) {
                st[i][j] = std::min(st[i - 1][j], st[i - 1][j + pow_value]);
            } else break;
        }
        pow_value *= 2;
    }

    return st;
}

std::vector<int> ProcessRequests(const std::vector<int>& numbers, const std::vector<Request>& requests) {
    int k = (int)numbers.size()/4;

    std::vector<std::pair<int, int>> max_pow;
    int pow = 0;
    int pow_value = 1;
    max_pow.emplace_back(0, 0);
    for (int i = 1; i <= numbers.size()/4; ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2;
            ++pow;
        }
        max_pow.emplace_back(pow, pow_value);
    }

    std::future<std::vector<std::vector<int>>> as1 = std::async(spar_tables, std::ref(numbers),
                                                                std::ref(max_pow), pow, 0, k);

    std::future<std::vector<std::vector<int>>> as2 = std::async(spar_tables, std::ref(numbers),
                                                                std::ref(max_pow), pow, k, 2 * k);

    std::future<std::vector<std::vector<int>>> as3 = std::async(spar_tables, std::ref(numbers),
                                                                std::ref(max_pow), pow, 2 * k, 3 * k);

    std::vector<std::pair<int, int>> max_pow2 = max_pow;
    for (int i = (int)numbers.size()/4; i <= k + numbers.size() % 4; ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2; ++pow;
        }
        max_pow.emplace_back(pow, pow_value);
    }
    std::future<std::vector<std::vector<int>>> as4 = std::async(spar_tables, std::ref(numbers),
                                                                std::ref(max_pow2), pow, 3 * k, numbers.size());

    std::vector<std::vector<int>> st1 = as1.get();
    std::vector<std::vector<int>> st2 = as2.get();
    std::vector<std::vector<int>> st3 = as3.get();
    std::vector<std::vector<int>> st4 = as4.get();

    std::vector<int> answer;
    int tmp_min;
    for (auto elem : requests) {
        int l = elem.left, r = elem.right;
        int l_st = l/k + 1, r_st = r/k + 1;
        tmp_min = 2147483647;
        for (int i = l_st; i <= r_st; ++i) {
            int rr;
            if (i <= 3) rr = std::min(r, k * i - 1);
            else rr = r;

            int g, value_of_g;
            g = max_pow2[rr - l + 1].first;
            value_of_g = max_pow2[rr - l + 1].second;

            if (i == 1) {
                tmp_min = std::min(tmp_min, std::min(st1[g][l], st1[g][rr - value_of_g + 1]));
            } else if (i == 2) {
                tmp_min = std::min(tmp_min, std::min(st2[g][l - k], st2[g][rr - value_of_g + 1]));
            } else if (i == 3) {
                tmp_min = std::min(tmp_min, std::min(st3[g][l - 2 * k], st3[g][rr - value_of_g + 1]));
            } else if (i == 4) {
                tmp_min = std::min(tmp_min, std::min(st4[g][l - 3 * k], st4[g][rr - value_of_g + 1]));
            }
        }
        answer.push_back(tmp_min);
    }

    return answer;
}


int main() {
    const std::vector<int> numbers = {3, 1, 0, 4};
    const std::vector<Request> requests = {
            {0, 4},
            {0, 2},
            {1, 3},
            {3, 4}
    };
    for (int result : ProcessRequests(numbers, requests)) {
        std::cout << result << " ";
    }
    std::cout << std::endl;
    return 0;
    // ожидаемый вывод: 0 1 0 4
}