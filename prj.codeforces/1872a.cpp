#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
 
int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        int dif = std::abs(a - b);
        dif = dif / 2 + (dif % 2 == 1);
        std::cout << dif / c + (dif % c > 0) << '\n';
    }
}
