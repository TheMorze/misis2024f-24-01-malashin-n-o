#include <iostream>
#include <vector>
 
#define ll long long
 
int main() {
    ll n;
    std::cin >> n;
    int counter = 0;
    while (n > 0) {
        int d = n % 10;
        if (d == 4 or d == 7) counter++;
        n /= 10;
    }
    if (counter == 4 or counter == 7) std::cout << "YES";
    else std::cout << "NO";
}
