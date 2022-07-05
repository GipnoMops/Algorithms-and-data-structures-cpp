#include <iostream>
#include <vector>

using namespace std;

const int INF = 9;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n * m + 1, vector<int>(n * m + 1, INF));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int num_of_top = (i - 1) * m + j;

            if (num_of_top % m != 0) {
                g[num_of_top][num_of_top + 1] = 2;
                //g[num_of_top + 1][num_of_top] = 2;
            }
            if (num_of_top + m < n * m + 1) {
                //g[num_of_top + m][num_of_top] = 1;
                g[num_of_top][num_of_top + m] = 1;
            }

            int value;
            cin >> value;
            if (value == 2) {
                g[num_of_top + 1][num_of_top] = 0;
                g[num_of_top][num_of_top + 1] = 0;
            } else if (value == 1) {
                g[num_of_top + m][num_of_top] = 0;
                g[num_of_top][num_of_top + m] = 0;
            } else if (value == 3) {
                g[num_of_top + 1][num_of_top] = 0;
                g[num_of_top][num_of_top + 1] = 0;
                g[num_of_top + m][num_of_top] = 0;
                g[num_of_top][num_of_top + m] = 0;
            }
        }
    }

    vector<bool> used (n * m + 1);
    vector<int> min_e (n * m + 1, INF), sel_e (n * m + 1, -1);
    min_e[1] = 0;
    int ansver = 0;
    int kol = 0;
    vector<int> print;
    for (int i = 0; i < n * m; ++i) {
        int v = -1;
        for (int j = 1; j <= n * m; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;

        used[v] = true;
        if (sel_e[v] != -1) {
            ansver += g[sel_e[v]][v];
            if (g[sel_e[v]][v] != 0) {
                ++kol;
                print.push_back(((min(sel_e[v], v) - 1) / m) + 1);
                if (min(sel_e[v], v) % m != 0)
                    print.push_back(min(sel_e[v], v) % m);
                else
                    print.push_back(m);
                print.push_back(g[sel_e[v]][v]);
            }
        }

        for (int to = 1; to <= n * m; ++to)
            if (g[v][to] < min_e[to]) {
                min_e[to] = g[v][to];
                sel_e[to] = v;
            }
    }
    cout << kol << " " << ansver << "\n";

    int flag = 0;
    for (auto& elem : print) {
        cout << elem << " ";
        ++flag;
        if (flag % 3 == 0)
            cout << "\n";
    }
}

