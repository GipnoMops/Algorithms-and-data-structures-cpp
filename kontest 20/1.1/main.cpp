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


std::vector<int> RMQ(const std::vector<int>& numbers, const std::vector<Request>& requests) {
    std::vector<std::pair<int, int>> max_pow;
    int pow = 0;
    int pow_value = 1;
    max_pow.emplace_back(0, 0);
    for (int i = 1; i <= numbers.size(); ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2;
            ++pow;
        }
        max_pow.emplace_back(pow, pow_value);
    }

    std::vector<std::vector<int>> pref(pow + 1, std::vector<int>(numbers.size()));
    pref[0] = numbers;
    pow_value = 1;
    for (int i = 1; i <= pow; ++i) {
        for (int j = 0; j < numbers.size(); ++j) {
            if (j + pow_value < numbers.size()) {
                pref[i][j] = std::min(pref[i - 1][j], pref[i - 1][j + pow_value]);
            } else break;
        }
        pow_value *= 2;
    }

    std::vector<int> answer;
    for (auto elem : requests) {
        int l = elem.left, r = elem.right - 1;

        int k, value_of_k;
        k = max_pow[r - l + 1].first;
        value_of_k = max_pow[r - l + 1].second;
        answer.push_back(std::min(pref[k][l], pref[k][r - value_of_k + 1]));
    }

    return answer;
}


std::vector<int> ProcessRequests(const std::vector<int>& numbers, const std::vector<Request>& requests) {
    if (numbers.size() < 4) return RMQ(numbers, requests);

    int k = (int)numbers.size()/4;

    std::vector<std::pair<int, int>> max_pow;
    int pow = 0, pow_value = 1;
    max_pow.emplace_back(0, 0);
    for (int i = 1; i <= numbers.size()/4; ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2; ++pow;
        }
        max_pow.emplace_back(pow, pow_value);
    }

    auto as1 = std::async(spar_tables, std::ref(numbers), std::ref(max_pow), pow, 0, k);
    auto as2 = std::async(spar_tables, std::ref(numbers), std::ref(max_pow), pow, k, 2 * k);
    auto as3 = std::async(spar_tables, std::ref(numbers), std::ref(max_pow), pow, 2 * k, 3 * k);

    std::vector<std::pair<int, int>> max_pow2 = max_pow;
    for (int i = (int)numbers.size()/4; i <= k + numbers.size() % 4; ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2; ++pow;
        }
        max_pow2.emplace_back(pow, pow_value);
    }

    auto as4 = std::async(spar_tables, std::ref(numbers), std::ref(max_pow2), pow, 3 * k, numbers.size());

    std::vector<std::vector<int>> st1 = as1.get();
    std::vector<std::vector<int>> st2 = as2.get();
    std::vector<std::vector<int>> st3 = as3.get();
    std::vector<std::vector<int>> st4 = as4.get();

    std::vector<int> answer;
    int tmp_min;
    for (auto elem : requests) {
        int l = elem.left, r = elem.right - 1;
        int l_st = std::min(l, k * 4 - 1)/k + 1, r_st =  std::min(r, k * 4 - 1)/k + 1;

        tmp_min = 2147483647;
        for (int i = l_st; i <= r_st; ++i) {
            int rr = r, ll = l;
            if (i <= 3) rr = std::min(r, k * i - 1);
            if (i > 1) ll = std::max(l, k * (i - 1));

            int g, value_of_g;
            g = max_pow2[rr - ll + 1].first;
            value_of_g = max_pow2[rr - ll + 1].second;

            if (i == 1) {
                tmp_min = std::min(tmp_min, std::min(st1[g][ll], st1[g][rr - value_of_g + 1]));
            } else if (i == 2) {
                tmp_min = std::min(tmp_min, std::min(st2[g][ll - k], st2[g][rr - value_of_g - k + 1]));
            } else if (i == 3) {
                tmp_min = std::min(tmp_min, std::min(st3[g][ll - 2 * k], st3[g][rr - value_of_g - 2 * k + 1]));
            } else if (i == 4) {
                tmp_min = std::min(tmp_min, std::min(st4[g][ll - 3 * k], st4[g][rr - value_of_g - 3 * k + 1]));
            }
        }
        answer.push_back(tmp_min);
    }
    return answer;
}


int main() {
    for (int test = 1; test <= 100000; ++test) {
        srand( time( 0 ) );

        std::vector<int> numbers;
        int random_n = rand() % 1000;
        for (int i = 0; i < random_n; ++i) {
            int random_elem = rand() % 2147483647;
            if (rand() % 2 == 0) random_elem *= -1;
            numbers.push_back(random_elem);
            //std::cout << random_elem << " ";
        }
        //std::cout << "\n";

        std::vector<Request> request; /* = {
            {0, 1},
            {0, 2},
            {0, 3},
            {0, 4},
            {1, 2},
            {1, 3},
            {1, 4},
            {2, 3},
            {2, 4},
            {3, 4},
    };*/

        for (int i = 0; i < numbers.size(); ++i) {
            for (int j = i + 1; j <= numbers.size(); ++j)
                request.push_back(Request{i, j});
        }

        const std::vector<Request> requests = request;

        auto answer1 = RMQ(numbers, requests);
        auto answer2 = ProcessRequests(numbers, requests);

        /*for (auto elem : answer1) std::cout << elem << " ";
        std::cout << "\n";
        for (auto elem : answer2) std::cout << elem << " ";
        std::cout << "\n";*/

        if (answer1 == answer2) continue;//std::cout << "OK ";
        else {
            std::cout << "\nWA\n";
            for (auto elem : numbers) std::cout << elem << " ";
            break;
        }
    }
    std::cout << "OK\n";
}