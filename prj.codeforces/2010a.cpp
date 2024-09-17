#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n;
        std::cin >> n;
        int res = 0;
        for (int j = 1; j <= n; ++j) {
            int a;
            std::cin >> a;
            if (j % 2 == 1) res += a;
            else res -= a;
        }
        std::cout << res << '\n';
    }
}
