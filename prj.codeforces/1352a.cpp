#include <iostream>
#include <vector>
#include <cmath>
 
 
int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        std::cin >> n;
        int counter = 0;
        std::vector<int> a(6);
        for (int i = 0; i < 6; i++) {
            a[i] = 0;
        }
        int res = 0;
        while (n != 0) {
            int d = n % 10;
            if (d > 0) {
                a[counter] = d * pow(10, counter);
                res++;
            }
            if (n == 1) break;
            n /= 10;
            counter++;
        }
        std::cout << res << '\n';
        for (int i = 5; i >= 0; i--) {
                if (a[i] != 0) std::cout << a[i] << ' ';
        }
        std::cout << '\n';
    }
}
