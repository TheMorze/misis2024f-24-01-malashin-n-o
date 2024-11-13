#include <iostream>

void solve() {
    int k = 0;
    int ans = 0;
    while (k < 100) {
        char el;
        std::cin >> el;
        int i = k / 10, j = k % 10;
        if (el == 'X') {
            if (i == 0 || i == 9 || j == 0 || j == 9) ans += 1;
            else if (j == 1 || i == 1 || j == 8 || i == 8) ans += 2;
            else if (i == 2 || j == 2 || i == 7 || j == 7) ans += 3;
            else if (i == 3 || j == 3 || i == 6 || j == 6) ans += 4;
            else if (i == 4 || j == 4 || i == 5 || j == 5) ans += 5;
        }
        k++;
    }
    std::cout << ans << '\n';
}


int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
}