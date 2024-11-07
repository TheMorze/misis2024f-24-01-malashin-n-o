#include <iostream>

void solve() {
    int n, k;
    std::string s;

    std::cin >> n >> k;
    std::cin >> s;

    bool flag = true;

    for (int i = 0; i < k; ++i) {
        int ex = -1;
        for (int j = i; j < n; j += k) {
            if (s[j] != '?' && ex == -1) {
                ex = s[j];
                break;
            }
        }

        if (ex != -1) {
            for (int j = i; j < n; j += k) {
                if (s[j] == '?') s[j] = ex;
                else if (s[j] != ex) {
                    flag = false;
                    break;
                }
            }
        }

        if (!flag) break;
    }

    if (flag) {
        int k0 = 0, k1 = 0, kV = 0;
        for (int i = 0; i < k; ++i) {
            if (s[i] == '0') k0++;
            else if (s[i] == '1') k1++;
            else kV++;
        }
        if (k0 > k / 2 || k1 > k / 2) flag = false;
    }



    if (flag) std::cout << "YES" << '\n';
    else std::cout << "NO" << '\n';


}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }

    return 0;
}
