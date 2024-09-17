#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
 
int main() {
    std::string s;
    std::cin >> s;
    for (size_t i = 1; i < s.size(); ++i) {
        for (int j = 1; j < i; ++j) {
            std::string sub1 = s.substr(0, i);
            std::string sub2 = s.substr(j, s.size() - 1);
            if (sub1 == sub2)
            {
                std::cout << "YES" << '\n' << s.substr(0, i);
                return 0;
            }
        }
    }
    std::cout << "NO";
}
