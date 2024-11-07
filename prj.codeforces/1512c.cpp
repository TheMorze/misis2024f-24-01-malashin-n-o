#include <iostream>
#include <string>

void solve() {
    int a, b;
    std::cin >> a >> b;

    std::string s;
    std::cin >> s;

    int k0 = 0, k1 = 0;
    int l = s.size();
    bool flag = false;

    for (size_t i = 0; i < l / 2; ++i) {
        if (s[i] == '?' && s[l - i - 1] != '?') {
            if (s[l - i - 1] == '0') {
                k0 += 2;
                s[i] = s[l - i - 1];
            }
            else {
                k1 += 2;
                s[i] = s[l - i - 1];
            }
        }

        else if (s[i] != '?' && s[l - i - 1] == '?') {
            if (s[i] == '0') {
                k0 += 2;
                s[l - i - 1] = s[i];
            }

            else {
                k1 += 2;
                s[l - i - 1] = s[i];
            }
        }




        else if (s[i] != '?' && s[l - i - 1] != '?') {
            if (s[i] != s[l - i - 1]) {
                flag = true;
                break;
            }
            else {
                if (s[i] == '0') k0 += 2;
                else k1 += 2;
            }
        }
    }

    if (!flag) {
        for (size_t i = 0; i < l / 2 + (l % 2); ++i) {

            // Для серединного элемента
            if (i == l - i - 1) {
                if (s[i] == '?') {
                    if ((a - k0) % 2 == 1) {
                        s[i] = '0';
                        k0++;
                    }
                    else if ((b - k1) % 2 == 1) {
                        s[i] = '1';
                        k1++;
                    }
                }
                else {
                    if (s[i] == '0') k0++;
                    else k1++;
                }
            }

            // Для остальных элементов
            else {
                if (s[i] == '?' && s[l - i - 1] == '?') {
                    if (a - k0 >= b - k1) {
                        s[i] = '0';
                        s[l - i - 1] = '0';
                        k0 += 2;
                    }
                    else {
                        s[i] = '1';
                        s[l - i - 1] = '1';
                        k1 += 2;
                    }
                }
            }

        }
        if (a == k0 && b == k1) std::cout << s << '\n';
        else std::cout << -1 << '\n';
    }

    else std::cout << -1 << '\n';
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        solve();
    }
}
