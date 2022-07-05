#include <iostream>
#include <set>
#include <vector>

bool k_ind_set(std::vector<std::vector<int>>& a, int a_size, int s) {
    std::set<int> M, G, K, P;
    int result = 0;
    for (int i = 0; i < a_size; ++i) K.insert(i);
    int v, Count = 0, cnt = 0;
    int Stack1[100];
    std::set<int> Stack2[100];
    std::set<int>::iterator theIterator;
    theIterator = K.begin();
    while ((!K.empty()) || (!M.empty())) {
        if (!K.empty()) {
            theIterator = K.begin();
            v = *theIterator;
            Stack2[++Count] = M;
            Stack2[++Count] = K;
            Stack2[++Count] = P;
            Stack1[++cnt] = v;
            M.insert(v);
            for (int i = 0; i < a_size; ++i) {
                if (a[v][i]) {
                    theIterator=K.find(i);
                    if (theIterator != K.end()) K.erase(theIterator);
                    theIterator = P.find(i);
                    if (theIterator != P.end()) P.erase(theIterator);
                }
            }
            theIterator = K.find(v);
            if (theIterator != K.end()) K.erase(theIterator);
        } else {
            if (P.empty()) {
                result = std::max(result, (int)M.size());
                if (result >= s) return true;
            }
            v = Stack1[cnt--];
            P = Stack2[Count--];
            K = Stack2[Count--];
            M = Stack2[Count--];
            theIterator = K.find(v);
            if (theIterator != K.end()) K.erase(theIterator);
            P.insert(v);
        }
    }

    if (result >= s) return true;
    return false;
}

int main() {
    int v, s, e;
    std::cin >> v >> s >> e;

     std::vector<std::vector<int>> g(v, std::vector<int>(v, 0));
     for (int i = 0; i < e; ++i) {
         int a, b;
         std::cin >> a >> b;
         g[a - 1][b - 1] = 1;
         g[b - 1][a - 1] = 1;
    }

     if (k_ind_set(g, v, s)) std::cout << "YES";
     else std::cout << "NO";
}
