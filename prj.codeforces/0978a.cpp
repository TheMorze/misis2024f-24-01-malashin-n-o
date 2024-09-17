#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
 
int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector<int> res;
    std::vector<int> wasNums;
    for (int i = 0; i < n; ++i) {
        bool flag = false;
        for (int j = i + 1; j < n; ++j) {
            if (a[i] == a[j]){
                flag = true;
            }
        }
        wasNums.push_back(a[i]);
        if(flag) {
            continue;
        } else {
            res.push_back(a[i]);
        }
    }
    std::cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); ++i) std::cout << res[i] << ' ';
 
}
