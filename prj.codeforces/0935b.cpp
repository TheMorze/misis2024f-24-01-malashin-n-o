#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int ans = 0;
    bool kd = true;
    int x = 0, y = 0;
    bool prev = false;

    for (int i = 0; i < n; ++i) {
        char d;
        std::cin >> d;

        if (d == 'U') y++;
        else if (d == 'R') x++;

        if (prev == true) {
            prev = false;
            if (kd == false && y > x) {
                ans++;
            }

            else if (kd == true && y < x) {
                ans++;
            }
        }

        if (x == y) prev = true;

        else if (y < x) kd = false;
        else if (y > x) kd = true;

    }

    std::cout << ans;
}
