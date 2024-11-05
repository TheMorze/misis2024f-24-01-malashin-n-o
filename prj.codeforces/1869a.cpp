#include <iostream>
#include <string>

int main() {
    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++ i) {
        int n;
        std::cin >> n;
        std::string s;
        std::cin >> s;
        if (!(n&1)) {
            std::cout << 2 << '\n';
            std::cout << 1 << ' ' << n << '\n';
            std::cout << 1 << ' ' << n << '\n';
        }
        else {
            std::cout << 4 << '\n';
            std::cout << 1 << ' ' << n - 1 << '\n';
            std::cout << 1 << ' ' << n - 1 << '\n';
            std::cout << n - 1 << ' ' << n << '\n';
            std::cout << n - 1 << ' ' << n << '\n';
        }
    }
}