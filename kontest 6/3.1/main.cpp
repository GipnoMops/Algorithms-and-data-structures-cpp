#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int INF = 100000;

int main() {
    int n, m;
    cin >> n >> m;

    struct point {
        int x;
        int y;
    };

    //vector<point> points( n * m + 1);
    vector<vector<int>> g(n * m + 1, vector<int>(n * m + 1, INF));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
           /* point top;
            top.x = j;
            top.y = i;
            points.push_back(top);*/
           int num_of_top = i * m + j;

           /*if (num_of_top % m != 0) {
               g[num_of_top][num_of_top + 1] = 1;
               g[num_of_top][num_of_top + 1] = 1;
           }
           if (num_of_top + m < n * m + 1) {
               g[num_of_top + m][num_of_top] = 2;
               g[num_of_top][num_of_top + m] = 2;
           }*/

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

            //cout << "(" << j << ", " << i << ")" << "\t";
        }
        //cout << "\n";
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cout << g[i][j] << "\t";
        }
        cout << "\n";
    }



    /*for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int value;
            cin >> value;
            g[i][j] = value;
        }
    }*/

    /*vector<bool> used (n * m + 1);
    vector<int> min_e (n * m + 1, INF), sel_e (n * m + 1, -1);
    min_e[1] = 0;
    int ansver = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 1; j <= n; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;

        used[v] = true;
        if (sel_e[v] != -1)
            ansver += g[v][sel_e[v]];

        for (int to = 1; to <= n; ++to)
            if (g[v][to] < min_e[to]) {
                min_e[to] = g[v][to];
                sel_e[to] = v;
            }
    }
    cout << ansver;*/
}

