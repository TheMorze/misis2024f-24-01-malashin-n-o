#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
 
int main() {
    int n;
    std::cin >> n;
    std::string s;
    int res = 0;
    std::cin >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'x') {
            int counter = 1;
            int j = i + 1;
            while (j < s.size() && s[j] == 'x') {
                counter++;
                j++;
            }
            if (counter > 2) res += counter - 2;
            if (j < s.size()) i = j;
            else if (j == n) break;
        }
    }
    std::cout << res;
}
