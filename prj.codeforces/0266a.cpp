#include <iostream>
#include <string>

int main() {
    int n;
    std::string s;
    std::string res;

    std::cin >> n >> s;

    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            ans++;
            s[i] = '*';
        }
    }

    std::cout << ans;


}