#include <iostream>

int main() {
    int a, b;
    std::cin >> a >> b;

    int x = 0;
    while (a <= b) {
        x++;
        a *= 3;
        b *= 2;
    }

    std::cout << x;