#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> snowmans(n + 1);
    snowmans[0] = std::make_pair(-1, 0);

    int answer = 0;
    for (int i = 1; i <= n; ++i) {
        int kop, wei;
        std::cin >> kop >> wei;
        if (wei != 0) {
            snowmans[i] = std::make_pair(kop, snowmans[kop].second + wei);
        } else {
            snowmans[i] = snowmans[snowmans[kop].first];
        }
        answer += snowmans[i].second;
    }

    std::cout << answer;
    return 0;
}
