#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        int n, x;
        std::cin >> n >> x;
        std::vector<int> vec(n);
        for (int j = 0; j < n; ++j) std::cin >> vec[j];
        int v = 1;
        int k = 0;
        while (k <= x) {
            for (int p = 1; p <= v; ++p) {
                if (std::find(vec.begin(), vec.end(), p) == vec.end()) k++;
            }
            if (k <= x)
            {
                k = 0;
                v++;
            }
        }
        std::cout << v - 1 << '\n';
    }
}
