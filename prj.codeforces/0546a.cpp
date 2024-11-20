#include <iostream>


int main() {
    int k, n, w;
    std::cin >> k >> n >> w;

    n -= k * (((1 + w) * w) / 2);
    n = - n;
    if (n > 0) std::cout << n;
    else std::cout << 0;

}