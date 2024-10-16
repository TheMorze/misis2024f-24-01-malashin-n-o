#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, m, sx, sy, d;
        std::cin >> n >> m >> sx >> sy >> d;
        if (std::min(sx - 1, m - sy) <= d && std::min(n - sx, sy - 1) <= d) std::cout << -1 << '\n';
        else std::cout << n + m - 2 << '\n';
    }
}
