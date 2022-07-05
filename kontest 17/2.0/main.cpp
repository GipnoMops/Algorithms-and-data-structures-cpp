#include <iostream>
#include <vector>

/*std::vector<int> prefix_function (std::string s) {
    int n = (int)s.length();
    std::vector<int> answer(n);
    for (int i = 0; i < n; ++i)
        for (int k = 0; k <= i; ++k)
            if (s.substr(0, k) == s.substr(i - k + 1, k))
                answer[i] = k;
    return answer;
}*/


int main() {
    std::string input;
    std::cin >> input;
    int n = (int)input.length();

    std::vector<int> answer(n);
    for (int i = 1; i < n; ++i) {
        int j = answer[i - 1];
        while (j > 0 && input[i] != input[j]) j = answer[j - 1];
        if (input[i] == input[j])  ++j;
        answer[i] = j;
    }

    int num = answer[(int)answer.size() - 1];
    for (int i = (int)answer.size() - num, j = 1; i < (int)answer.size(); ++i, ++j) {
        if (answer[i] != j) {
            num = 0; break;
        }
    }

    std::cout << answer.size() - num;
    return 0;
}
