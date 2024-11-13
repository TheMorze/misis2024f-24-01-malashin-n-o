#include <iostream>
#include <algorithm>

int main() {
    unsigned long long int n, m;
    std::cin >> n >> m;

    unsigned long long int ans = 0;
    unsigned long long int curPos = 1;
    for (int i = 0; i < m; ++i) {
        unsigned long long int pos;
        std::cin >> pos;
        if (pos < curPos) ans += (n - curPos + pos);
        else ans += (pos - curPos);
        curPos = pos;
    }
    std::cout << ans;
}