#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::string s;
    std::vector<char> v;

    std::cin >> s;
    int k = 0;

    for (size_t i = 0; i < s.size(); ++i) {
        if (std::find(v.begin(), v.end(), s[i]) == v.end()) {
            k++;
            v.push_back(s[i]);
        }
    }
    if (k % 2 == 1) {
        std::cout << "IGNORE HIM!";
    }
    else {
        std::cout << "CHAT WITH HER!";
    }
}