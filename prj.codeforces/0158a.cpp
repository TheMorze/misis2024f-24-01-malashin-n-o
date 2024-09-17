#include <iostream>
#include <vector>
 
#define ll long long
 
int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    int ps = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        if (i == k - 1) ps = a[i];
    }
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] >= ps and a[i] > 0) res++;
    }
    std::cout << res;
 
}
