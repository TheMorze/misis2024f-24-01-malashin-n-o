#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>



int main() {
    std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);

    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, k;
        std::string s;
        std::cin >> n >> s >> k;
        std::unordered_set<char> v(k);
        for (int j = 0; j < k; ++j) {
            char c;
            std::cin >> c;
            v.insert(c);
        }

        int lastIndx = 0;
        int ans = 0;
        for (int j = 1; j < n; ++j) {
            if (v.find(s[j]) != v.end()) {
                ans = std::max(j - lastIndx, ans);
                lastIndx = j;
                if (n - j < ans) break;
            }
        }
        std::cout << ans << '\n';

    }
}