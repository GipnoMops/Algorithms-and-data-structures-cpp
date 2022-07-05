#include <iostream>
#include <vector>

int main() {
    int m, n;
    bool flag = false;
    std::cin >> m >> n;
    std::vector<char> prime (n + 1, true);
    prime[0] = prime[1] = false;
    for (int i = 2; i <= n; ++i)
        if (prime[i]) {
            if (i * 1ll * i <= n) {
                if (i >= m) {
                    std::cout << i << "\n";
                    flag = true;
                }
                for (int j = i * i; j <= n; j += i)
                    prime[j] = false;
            } else
                for(; i <= n; ++i)
                    if (i >= m && prime[i]) {
                        std::cout << i << "\n";
                        flag = true;
                    }
        }


    if (!flag) std::cout << "Absent\n";

    /*std::cin >> m >> n;
    std::vector<char> prime (n+1, true);
    prime[0] = prime[1] = false;
    for (int i=2; i<=n; ++i)
        if (prime[i])
            if (i * 1ll * i <= n)
                for (int j=i*i; j<=n; j+=i)
                    prime[j] = false;

    for (int i = 2; i <= n; ++i)
        if (prime[i]) std::cout << i << " ";*/
    return 0;
}
