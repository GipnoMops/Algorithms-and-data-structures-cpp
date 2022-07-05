#include <iostream>
#include <vector>
#include <set>

bool k_ind_set(std::vector<std::vector<int>>& a, int size, int find_k) {
    std::set<int> M, G, K, P;
    int rez = 0;
    for (int i = 0; i < size; ++i) K.insert(i);
    int v, Count = 0, cnt = 0;
    std::vector<int> Stack1(2 * size);
    std::set<int> Stack2[100];
    auto theIterator = K.begin();
    while ((!K.empty()) || (!M.empty())) {
        if (!K.empty()) {
            theIterator = K.begin();
            v = *theIterator;
            Stack2[++Count] = M;
            Stack2[++Count] = K;
            Stack2[++Count] = P;
            Stack1[++cnt] = v;
            M.insert(v);
            for (int i = 0; i < size; ++i) {
                if (a[v][i]) {
                    theIterator=K.find(i);
                    if (theIterator != K.end()) K.erase(theIterator);
                    theIterator =  P.find(i);
                    if (theIterator != P.end()) P.erase(theIterator);
                }
            }
            theIterator = K.find(v);
            if (theIterator != K.end()) K.erase(theIterator);
        } else {
            if (P.empty()) {
                rez = std::max(rez, (int)M.size());
                if(rez >= find_k) return true;
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
