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


            /* for (int i = 1; i <= n; ++i) {
                 for (int j = 1; j <= m; ++j) {
                     if (j != n)
                         g[i][j + 1] = 2;
                     if (i != 1)
                         g[i + 1][j] = 1;

                     int value;
                     cin >> value;
                     if (value == 1)
                         g[i][j + 1] = 0;
                     else if (value == 2)
                         g[i + 1][j] = 0;
                     else if (value == 3){
                         g[i][j + 1] = 0;
                         g[i + 1][j] = 0;
                     }

                     cout << g[i][j] << " ";
                 }
                 cout << "\n";
             }*/

    /*for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            double len = sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x)
                    + (points[i].y - points[j].y) * (points[i].y - points[j].y));
            g[i][j] = len;
            g[j][i] = len;
        }
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int top1, top2;
        cin >> top1 >> top2;

        for (int k = 1; k <= n; ++k) {
            if (k != top1 && k != top2) {
                double len1 = sqrt((points[top1].x - points[k].x) * (points[top1].x - points[k].x)
                                   + (points[top1].y - points[k].y) * (points[top1].y - points[k].y));
                double len2 = sqrt((points[top2].x - points[k].x) * (points[top2].x - points[k].x)
                                   + (points[top2].y - points[k].y) * (points[top2].y - points[k].y));

                if (len1 + len2 == g[top1][top2]) {
                    g[k][top1] = 0.0;
                    g[top1][k] = 0.0;
                    g[k][top2] = 0.0;
                    g[top2][k] = 0.0;
                }
            }
        }

        g[top1][top2] = 0.0;
        g[top2][top1] = 0.0;


    }*/

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
    cout << ansver;
}
