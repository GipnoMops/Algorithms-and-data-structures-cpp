#include <iostream>
#include <string>
#include <unordered_map>


int main() {
    std::unordered_map<int, std::string> map;
    std::unordered_map<std::string, int> map2;
    for (int i = 0; i <= 127; ++i) {
        map[i] = std::string(1, static_cast<char>(i));
        map2[std::string(1, static_cast<char>(i))] = i;
    }
    int word = 128;

    int k;
    std::cin >> k;

    std::string tmp;
    for (int i = 0; i < k; ++i) {
        int num;
        std::cin >> num;
        std::cout << map[num];
        for (auto lett : map[num]) {
            tmp += lett;
            if (map2[tmp] != 0) continue;
            else {
                map2[tmp] = word++;
                map[word - 1] = tmp;
                tmp = tmp.substr(tmp.size() - 1, 1);
            }
        }
    }
    return 0;
}
