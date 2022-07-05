/*#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const long double INF = 100000.0;

int main() {
    int n;
    cin >> n;

    struct point {
        int x;
        int y;
    };

    vector<point> points(n + 1);
    vector<vector<long double>> g(n + 1, vector<long double>(n + 1, INF));
    for (int i = 1; i <= n; ++i) {
        point top;
        cin >> top.x >> top.y;
        points[i] = top;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            long double len = sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x)
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
                int len1 = ((points[top1].x - points[k].x) * (points[top1].x - points[k].x)
                                   + (points[top1].y - points[k].y) * (points[top1].y - points[k].y));
                int len2 = ((points[top2].x - points[k].x) * (points[top2].x - points[k].x)
                                   + (points[top2].y - points[k].y) * (points[top2].y - points[k].y));
                int len3 = ((points[top2].x - points[top1].x) * (points[top2].x - points[top1].x)
                            + (points[top2].y - points[top1].y) * (points[top2].y - points[top1].y))
                            //* ((points[top2].x - points[top1].x) * (points[top2].x - points[top1].x)
                            //+ (points[top2].y - points[top1].y) * (points[top2].y - points[top1].y));

                cout << len1 << " " << len2 << " " << len3 << "\n";
                if ((len1 + len2) == len3) {
                    g[k][top1] = 0.0;
                    g[top1][k] = 0.0;
                    g[k][top2] = 0.0;
                    g[top2][k] = 0.0;
                }
            }
        }

        g[top1][top2] = 0.0;
        g[top2][top1] = 0.0;


    }

    vector<bool> used (n + 1);
    vector<long double> min_e (n + 1, INF);
    vector<int> sel_e (n + 1, -1);
    min_e[1] = 0.0;
    long double ansver = 0.0;
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
    cout << ansver;
}
*/


/*#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const long double INF = 100000.0;

int main() {
    int n;
    cin >> n;

    struct point {
        int x;
        int y;
    };

    vector<point> points(n + 1);
    vector<vector<long double>> g(n + 1, vector<long double>(n + 1, INF));
    for (int i = 1; i <= n; ++i) {
        point top;
        cin >> top.x >> top.y;
        points[i] = top;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            long double len = sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x)
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
                long double len1 = sqrt(points[top1].x - points[k].x) * (points[top1].x - points[k].x)
                                   + (points[top1].y - points[k].y) * (points[top1].y - points[k].y);
                long double len2 = sqrt(points[top2].x - points[k].x) * (points[top2].x - points[k].x)
                                   + (points[top2].y - points[k].y) * (points[top2].y - points[k].y);
                //long double len3 = (points[top1].x - points[top2].x) * (points[top1].x - points[top2].x)
                //              + (points[top1].y - points[top2].y) * (points[top1].y - points[top2].y);

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


    }

    vector<bool> used (n + 1);
    vector<long double> min_e (n + 1, INF);
    vector<int> sel_e (n + 1, -1);
    min_e[1] = 0.0;
    long double ansver = 0.0;
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
    cout << ansver;
}*/


#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const long double INF = 100000.0;

int main() {
    int n;
    cin >> n;

    struct point {
        int x;
        int y;
    };

    vector<point> points(n + 1);
    vector<vector<long double>> g(n + 1, vector<long double>(n + 1, INF));
    for (int i = 1; i <= n; ++i) {
        point top;
        cin >> top.x >> top.y;
        points[i] = top;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            long double len = sqrt((points[i].x - points[j].x) * (points[i].x - points[j].x)
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
                if (fabs(g[top1][k] + g[top2][k] - g[top1][top2]) < 3 * 1.0e-6) {
                    g[k][top1] = 0.0;
                    g[top1][k] = 0.0;
                    g[k][top2] = 0.0;
                    g[top2][k] = 0.0;
                }
            }
        }

        g[top1][top2] = 0.0;
        g[top2][top1] = 0.0;


    }

    vector<bool> used (n + 1);
    vector<long double> min_e (n + 1, INF);
    vector<int> sel_e (n + 1, -1);
    min_e[1] = 0.0;
    long double ansver = 0.0;
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
    cout << fixed << setprecision(5) << ansver << "\n";
}


/*#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    long double x = 10.00687692834;
    cout << x << "\n";
    cout << fixed << setprecision(5) << x << "\n";
    return 0;
}*/