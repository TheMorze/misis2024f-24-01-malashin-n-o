#include <iostream>
#include <string>

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::string s;
    std::cin >> s;

    int ans = 0;

    for (int i = 0; i < n; i++) {
            if (s[i] == 'B') {
                ans++;
                i += k - 1;
            }
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