#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
int main() {
    int a, b;
    std::cin >> a >> b;
    std::vector<int> v(3, 0);
    v[a] = a;
    v[b] = b;
    for (int i = 1; i <= 3; ++i) {
        if (v[i] == 0) std::cout << i;
    }
}
