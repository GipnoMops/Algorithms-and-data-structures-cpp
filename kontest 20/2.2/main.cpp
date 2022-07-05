#include <iostream>
#include <vector>
#include <variant>

struct ComputeRequest { int left; int right; };
struct UpdateRequest { int index; int delta; };
using Request = std::variant<ComputeRequest, UpdateRequest>;

int F (int a) {
    return a & (a + 1);
}

long long int pref_sum (int r, std::vector<long long int>& t) {
    long long int sum = 0;
    while (r >= 0) {
        sum += t[r];
        r = F(r) - 1;
    }
    return sum;
}

long long int segment_sum (int l, int r, std::vector<long long int>& t) {
    if (l == 0)
        return pref_sum(r, t);
    return pref_sum(r, t) - pref_sum(l - 1, t);
}

void inc(int i, int delta, std::vector<long long int>& t) {
    while (i < t.size()) {
        t[i] += delta;
        i = i | (i + 1);
    }
}

std::vector<int> ProcessRequests(const std::vector<int>& numbers, const std::vector<Request>& requests) {
    std::vector<long long int> t(numbers.size(), 0);
    for (int i = 0; i < numbers.size(); ++i)
        inc(i, numbers[i], t);

    std::vector<int> answer;
    for (auto request : requests) {
        if (std::holds_alternative<ComputeRequest>(request)) {
            ComputeRequest c_r = std::get<ComputeRequest>(request);
            int l = c_r.left, r = c_r.right - 1;
            answer.push_back(segment_sum(l, r, t));
        } else {
            UpdateRequest c_r = std::get<UpdateRequest>(request);
            int k = c_r.index, x = c_r.delta;
            inc(k, x, t);
        }
    }
    return answer;
}


int main() {
    const std::vector<int> numbers = {3, 1, 0, 4};
    const std::vector<Request> requests = {
            ComputeRequest{0, 4},
            ComputeRequest{0, 2},
            ComputeRequest{1, 3},
            ComputeRequest{3, 4},
            UpdateRequest{1, 10},
            UpdateRequest{3, 20},
            ComputeRequest{0, 4},
            ComputeRequest{0, 2},
            ComputeRequest{1, 3},
            ComputeRequest{3, 4},
    };
    for (int result : ProcessRequests(numbers, requests)) {
        std::cout << result << " ";
    }
    std::cout << std::endl;
    // ожидаемый вывод: 8 4 1 4 38 14 11 24
}
