#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> points;
    std::vector<int> left_to_right;
    std::vector<int> right_to_left;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        if (i > 0) {
            if (y > (points.back().second))
                left_to_right.push_back(left_to_right.back() +
                y - points.back().second);
            else left_to_right.push_back(left_to_right.back());

            if (points.back().second > y)
                right_to_left.push_back(points.back().second - y);
            else right_to_left.push_back(0);
        } else left_to_right.push_back(0);
        points.emplace_back(x, y);
    }

    //for (auto elem : right_to_left) std::cout << elem << " ";
    //std::cout << "\n";

    std::reverse(right_to_left.begin(), right_to_left.end());
    for (int i = 1; i < n; ++i) right_to_left[i] = right_to_left[i - 1] + right_to_left[i];



    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int start, end;
        std::cin >> start >> end;
        if (start < end) std::cout << left_to_right[end - 1] - left_to_right[start - 1] << "\n";
        else std::cout << right_to_left[right_to_left.size() - end - 1] -
        right_to_left[right_to_left.size() - start - 1] << "\n";
    }
    return 0;
}