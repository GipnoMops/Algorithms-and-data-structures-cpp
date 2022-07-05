#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int INF = 100000;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n + 1, vector<int>(m + 1, INF));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int value;
            cin >> value;
            g[i][j] = value;
        }
    }

    vector<vector<bool>> used (n + 1, vector<bool>(m + 1));
    vector<vector<int>> min_e (n + 1, vector<int>(m + 1, INF));
    vector<vector<pair<int, int>>> sel_e (n + 1, vector<pair<int, int>>(m + 1, make_pair(-1, -1)));
    min_e[1][1] = 0;
    int ansver = 0;
    int kol = 0;
    vector<int> print;
    for (int i = 0; i < n; ++i) {
        pair<int, int> v = make_pair(-1, -1);
        for (int j = 1; j <= n; ++j)
            for (int k = 1; k <= m; ++k)
                if (!used[j][k] && (v == make_pair(-1, -1) || min_e[j][k] < min_e[v.first][v.second]))
                    v = make_pair(j, k);

        used[v.first][v.second] = true;
        if (sel_e[v.first][v.second] != make_pair(-1, -1)) {


            if (v.first - sel_e[v.first][v.second].first == 1 ||
                v.first - sel_e[v.first][v.second].first == -1) {
                if (g[sel_e[v.first][v.second].first][sel_e[v.first][v.second].second] == 0 ||
                    g[sel_e[v.first][v.second].first][sel_e[v.first][v.second].second] == 2) {
                    print.push_back(v.first);
                    print.push_back(v.second);
                    ++ansver;
                    ++kol;
                    print.push_back(1);
                }

            }

            if (v.second - sel_e[v.first][v.second].second == 1 ||
                v.second - sel_e[v.first][v.second].second == -1) {
                if (g[sel_e[v.first][v.second].first][sel_e[v.first][v.second].second] == 0 ||
                    g[sel_e[v.first][v.second].first][sel_e[v.first][v.second].second] == 1) {
                    print.push_back(v.first);
                    print.push_back(v.second);
                    ansver += 2;
                    ++kol;
                    print.push_back(2);
                }
            }
        }


        if (g[v.first][v.second] == 0) {
            if (v.first != n)
                min_e[v.first + 1][v.second] = 1;
            if (v.second != m)
                min_e[v.first][v.second + 1] = 2;
        } else if (g[v.first][v.second] == 1) {
            min_e[v.first + 1][v.second] = 0;
        } else if (g[v.first][v.second] == 2) {
            min_e[v.first][v.second + 1] = 0;
        } else if (g[v.first][v.second] == 3) {
            min_e[v.first + 1][v.second] = 0;
            min_e[v.first][v.second + 1] = 0;
        }
    }
    cout << ansver << " " << kol;
}
