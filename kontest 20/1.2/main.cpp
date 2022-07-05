#include <algorithm>
#include <execution>
#include <future>
#include <iostream>
#include <random>
#include <sstream>
#include <vector>

#include "profile.h"


using i64 = int64_t;

struct Request {
    i64 left;
    i64 right;
    Request(i64 left, i64 right) : left(left), right(right) {
    }
};

i64 SumNaive(const std::vector<i64>& vec, i64 left, i64 right) {
    i64 sum = vec[left];
    for (i64 i = left + 1; i < right; ++i) {
        sum += vec[i];
    }
    return sum;
}

std::string ToString(const std::vector<i64>& vec) {
    std::stringstream ss;
    for (i64 i : vec) {
        ss << i << ",";
    }
    return ss.str();
}

std::vector<i64> GenerateVector(i64 size, i64 maxValue) {
    std::vector<i64> result;
    result.reserve(size);
    for (i64 i = 0; i < size; ++i) {
        i64 value = rand() % (maxValue + 1);
        result.push_back(value);
    }
    return result;
}


// minimum on [left, right)
std::vector<i64> ProcessRequestsNaive(const std::vector<i64>& numbers, const std::vector<Request>& requests) {
    std::vector<i64> result;
    result.reserve(requests.size());
    for (const Request& request : requests) {
        i64 min = numbers[request.left];
        for (i64 i = request.left + 1; i < request.right; ++i) {
            min = std::min(min, numbers[i]);
        }
        result.push_back(min);
    }
    return result;
}





std::vector<std::vector<i64>> spar_tables(const std::vector<i64>& num,
                                          std::vector<std::pair<i64, i64>>& max_pow,
                                          i64 pow, i64 l, i64 r) {

    std::vector<std::vector<i64>> st(pow + 1, std::vector<i64>(r - l));
    for (i64 i = l; i < r; ++i) st[0][i - l] = num[i];
    i64 pow_value = 1;
    for (i64 i = 1; i <= pow; ++i) {
        for (i64 j = 0; j < r - l; ++j) {
            if (j + pow_value < r) {
                st[i][j] = std::min(st[i - 1][j], st[i - 1][j + pow_value]);
            } else break;
        }
        pow_value *= 2;
    }

    return st;
}


std::vector<i64> RMQ(const std::vector<i64>& numbers, const std::vector<Request>& requests) {
    std::vector<std::pair<i64, i64>> max_pow;
    i64 pow = 0;
    i64 pow_value = 1;
    max_pow.emplace_back(0, 0);
    for (i64 i = 1; i <= numbers.size(); ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2;
            ++pow;
        }
        max_pow.emplace_back(pow, pow_value);
    }

    std::vector<std::vector<i64>> pref(pow + 1, std::vector<i64>(numbers.size()));
    pref[0] = numbers;
    pow_value = 1;
    for (i64 i = 1; i <= pow; ++i) {
        for (i64 j = 0; j < numbers.size(); ++j) {
            if (j + pow_value < numbers.size()) {
                pref[i][j] = std::min(pref[i - 1][j], pref[i - 1][j + pow_value]);
            } else break;
        }
        pow_value *= 2;
    }

    std::vector<i64> answer;
    for (auto elem : requests) {
        i64 l = elem.left, r = elem.right - 1;

        i64 k, value_of_k;
        k = max_pow[r - l + 1].first;
        value_of_k = max_pow[r - l + 1].second;
        answer.push_back(std::min(pref[k][l], pref[k][r - value_of_k + 1]));
    }

    return answer;
}


std::vector<i64> ProcessRequests(const std::vector<i64>& numbers, const std::vector<Request>& requests) {
    if (numbers.size() < 4) return RMQ(numbers, requests);

    i64 k = (i64)numbers.size()/4;

    std::vector<std::pair<i64, i64>> max_pow;
    i64 pow = 0, pow_value = 1;
    max_pow.emplace_back(0, 0);
    for (i64 i = 1; i <= numbers.size()/4; ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2; ++pow;
        }
        max_pow.emplace_back(pow, pow_value);
    }

    auto as1 = std::async(spar_tables, std::ref(numbers), std::ref(max_pow), pow, 0, k);
    auto as2 = std::async(spar_tables, std::ref(numbers), std::ref(max_pow), pow, k, 2 * k);
    auto as3 = std::async(spar_tables, std::ref(numbers), std::ref(max_pow), pow, 2 * k, 3 * k);

    std::vector<std::pair<i64, i64>> max_pow2 = max_pow;
    for (i64 i = (i64)numbers.size()/4; i <= k + numbers.size() % 4; ++i) {
        if (2 * pow_value <= i) {
            pow_value *= 2; ++pow;
        }
        max_pow2.emplace_back(pow, pow_value);
    }

    auto as4 = std::async(spar_tables, std::ref(numbers), std::ref(max_pow2), pow, 3 * k, numbers.size());

    std::vector<std::vector<i64>> st1 = as1.get();
    std::vector<std::vector<i64>> st2 = as2.get();
    std::vector<std::vector<i64>> st3 = as3.get();
    std::vector<std::vector<i64>> st4 = as4.get();

    std::vector<i64> answer;
    i64 tmp_min;
    for (auto elem : requests) {
        i64 l = elem.left, r = elem.right - 1;
        i64 l_st = std::min(l, k * 4 - 1)/k + 1, r_st =  std::min(r, k * 4 - 1)/k + 1;

        tmp_min = 2147483647;
        for (i64 i = l_st; i <= r_st; ++i) {
            i64 rr = r, ll = l;
            if (i <= 3) rr = std::min(r, k * i - 1);
            if (i > 1) ll = std::max(l, k * (i - 1));

            i64 g, value_of_g;
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
    std::cout << "brute force testing" << std::endl;
    for (i64 t = 0; t < 100; ++t) {
        i64 size = rand() % 5000000 + 1;
        std::vector<i64> vec = GenerateVector(size, 10000);
        std::vector<Request> requests;
        requests.reserve(10'000'000);
        for (i64 q = 0; q < requests.size(); ++q) {
            i64 left = rand() % vec.size();
            i64 right = rand() % vec.size();
            if (right < left) {
                std::swap(left, right);
            }
            right += 1;
            Request r(left, right);
            requests.push_back(r);
        }
        std::vector<i64> expected;
        std::vector<i64> result;
        {
            LOG_DURATION("naive");
            expected = ProcessRequestsNaive(vec, requests);
        }
        {
            LOG_DURATION("non-naive");
            std::vector<i64> result = ProcessRequests(vec, requests);
        }
        // std::cout << ToString(result) << std::endl;
        for (i64 i = 0; i < result.size(); ++i) {
            if (result[i] != expected[i]) {
                std::cerr << "Error in vec " << ToString(vec) << "; expected sum: " << expected[i]
                << " got " << result[i] << "; left: " << requests[i].left << "; right: " << requests[i].right << std::endl;
                throw std::runtime_error("...");
            }
        }
    }
    std::cout << "All done! "<< std::endl;
}