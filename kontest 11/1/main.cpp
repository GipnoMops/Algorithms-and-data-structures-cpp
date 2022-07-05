/*#include <iostream>
#include <vector>
#include <math.h>

int main() {
    long long int n;
    std::cin >> n;
    int sq = std::ceil(std::sqrt(n));
    std::vector<char> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (long long int i = 2; i <= sq; ++i)
        if (prime[i]) {
            if (n % i == 0) std::cout << i << " ";
            for (long long int j = i * i; j <= n; j += i)
                prime[j] = false;
        }
    return 0;
}
*/

#include <iostream>
#include <vector>

int main() {
    long long int n;
    std::cin >> n;
    std::vector<char> prime(n + 1, true);
    prime[0] = prime[1] = false;
    for (long long int i = 2; i <= n; ++i)
        if (prime[i]) {
            while (n % i == 0) {
                n /= i;
                std::cout << i << " ";
            }
            for (long long int j = i * i; j <= n; j += i)
                prime[j] = false;
        }
    return 0;
}
