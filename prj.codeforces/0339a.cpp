#include <iostream>

int main() {
    int c1 = 0, c2 = 0, c3 = 0;
    int curd;
    while (std::cin >> curd) {
        if (curd == 1) c1++;
        else if (curd == 2) c2++;
        else if (curd == 3) c3++;
    }

    for (int i = 0; i < c1 + c2 + c3; ++i) {
        if (i < c1) {
            if (i != c1 + c2 + c3 - 1) std::cout << 1 << '+';
            else std::cout << 1;
        }
        else if (i < c1 + c2) {
            if (i != c1 + c2 + c3 - 1) std::cout << 2 << '+';
            else std::cout << 2;
        }
        else {
            if (i != c1 + c2 + c3 - 1) std::cout << 3 << '+';
            else std::cout << 3;
        }
    }
}