#include <iostream>
 
int main() {
    int x;
    std::cin >> x;
    std::cout << x / 5 + int((x % 5) > 0);
}
 
