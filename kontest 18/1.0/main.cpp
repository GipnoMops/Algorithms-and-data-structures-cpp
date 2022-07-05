#include <iostream>
#include <vector>
#include <string>


int main() {
    std::string string;
    std::cin >> string;
    int len = string.length();

    int counter = 0;
    int n = len;
    if (n == 1) counter = 2;
    else if (n == 3) counter = 3;
    else {
        while (n != 0) {
            n /= 2; ++counter;
        }
    }

    int counter2 = 0;
    len += counter;
    while (len != 0) {
        len /= 2; ++counter2;
    }
    counter = counter2;

    std::vector<int> answer(string.length() + counter, 0);
    int two_deg = 1;
    auto it = string.begin();
    for (int i = 0; i < answer.size(); ++i) {
        if (i + 1 == two_deg) {
            two_deg *= 2; continue;
        }
        if (*it == 49) answer[i] = 1;
        else answer[i] = 0;
        ++it;
    }

    std::vector<int> prefix(string.length() + counter, 0);
    for (int i = 1; i < answer.size(); ++i) prefix[i] = prefix[i - 1] + answer[i];


    for (int i = 1; i < answer.size(); i *= 2) {
        for (int j = i; j <= answer.size(); j += 2 * i) {
            if (j == 1) {
                answer[i - 1] += (prefix[std::min(j + i - 1, (int)answer.size() - 1)] - prefix[j - 1]) % 2;
                continue;
            } else answer[i - 1] += (prefix[std::min(j + i - 2, (int)answer.size() - 1)] - prefix[j - 2]) % 2;
        }
        answer[i - 1] %= 2;
    }

    for (auto elem : answer) std::cout << elem;
    return 0;
}

L  e   m   p   e   l   -  Z  i   v   -  W  e   l   c  h  (  L  Z  W  )  i  s   a   u  n  i  v   e   r   s   a   l   l   o   s  s   l   e   s   s   d   a   t  a   c  o  m   p   r   e   s   s   i   o   n   a   l   g   o   r   i   t   h   m   c  r  e  a    t   e   d   b  y  A   b  r  a  h  a  m   L   e   m   p   e   l ,  J  a  c   o  b   Z   i   v  ,  a    n  d   T   e   r   r   y   W   elch.
76 101 109 112 101 108 45 90 105 118 45 87 132 99 104 32 40 76 90 87 41 32 105 115 32 97 32 117 110 136 101 114 115 97 108 32 108 111 115 115 108 101 166 32 100 97 116 153 99 111 130 114 169 115 105 111 110 152 108 103 111 114 105 116 104 109 32 99 179 173 101 100 32 98 121 32 65 98 114 97 104 97 193 128 130 132 44 32 74 97 176 98 32 135 118 214 97 110 199 84 158 114 202 139 108 141 46
