#include <iostream>
#include <algorithm>

int main() {
    int n, k;
    std::cin >> n >> k;
    int ans = 100000;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        if (k % a == 0) ans = std::min(ans, k / a);
    }
    std::cout << ans;
}