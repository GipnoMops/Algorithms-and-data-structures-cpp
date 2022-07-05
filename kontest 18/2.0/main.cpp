#include <iostream>
#include <vector>
#include <string>


int main() {
    std::string string;
    std::cin >> string;
    int mistakes = 0;

    std::vector<int> answer;
    for (auto it = string.begin(); it < string.end(); ++it) answer.push_back(*it % 2);

    for (int i = 1; i <= answer.size(); i *= 2) {
        int sum = 0;
        int j = i;
        while (j <= answer.size()) {
            for (int k = 0; k < i; ++k) {
                if (j > answer.size()) break;
                if (j == i) {
                    ++j; continue;
                }
                sum += answer[j - 1]; ++j;
            }
            j += i;
        }
        if (answer[i - 1] != sum % 2) mistakes += i;
    }

    if (mistakes > 0) answer[mistakes - 1] = (answer[mistakes - 1] + 1) % 2;

    for (int i = 1, deg = 1; i <= answer.size(); ++i) {
        if (i == deg) {
            deg *= 2; continue;
        }
        std::cout << answer[i - 1];
    }
    return 0;
}
