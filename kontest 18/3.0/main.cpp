#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {
    std::unordered_map<std::string, int> map;
    for (int i = 0; i <= 127; ++i) map[std::string(1, static_cast<char>(i))] = i;
    int word = 128;

    std::string text;
    std::getline(std::cin, text);
    std::string tmp = "";
    std::vector<int> answer;
    for (auto it = text.begin(); it < text.end(); ++it) {
        tmp += *it;
        if (map[tmp] != 0) continue;
        else {
            answer.push_back(map[tmp.substr(0, tmp.size() - 1)]);
            map[tmp] = word++;
            tmp = tmp.substr(tmp.size() - 1, 1);
        }
    }

    if (!tmp.empty()) answer.push_back(map[tmp]);
    std::cout << answer.size() << "\n";
    for (auto elem : answer) std::cout << elem << " ";
    return 0;
}
