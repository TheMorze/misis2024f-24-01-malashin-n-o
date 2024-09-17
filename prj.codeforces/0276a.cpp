#include <iostream>
#include <vector>
 
#define ll long long
 
int main() {
    ll n, k;
    std::cin >> n >> k;
    ll res = -100000000000;
    for (ll i = 0; i < n; i++) {
        ll f, t, pls;
        std::cin >> f >> t;
        if (t > k) pls = f - (t - k);
        else pls = f;
        if (pls > res) res = pls;
    }
    std::cout << res;
}
