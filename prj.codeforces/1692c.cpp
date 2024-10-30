#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;
    for (int k = 0; k < t; ++k) {
        std::vector<std::vector<char>> v(8, std::vector<char>(8, '.'));
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::cin >> v[i][j];
            }
        }

        for (int i = 1; i < 7; ++i) {
            for (int j = 1; j < 7; ++j) {
                if (v[i + 1][j + 1] == '#' && v[i + 1][j-1] == '#' && v[i - 1][j + 1] == '#' && v[i - 1][j - 1] == '#') {
                    std::cout << i + 1 << ' ' << j + 1;
                }
            }
        }
        std::cout << '\n';

    }
}