#include <iostream>
 
int main() {
    int y;
    std::cin >> y;
    int cur = y + 1;
    while (true) {
        int d1 = cur / 1000, d2 = cur / 100 % 10, d3 = cur / 10 % 10, d4 = cur % 10;
 
        if (d1 != d2 and d1 != d3 and d1 != d4 and d2 != d3 and d2 != d4 and d3 != d4) {
            std::cout << cur;
            break;
        }
        else {cur++;}
    }
}
