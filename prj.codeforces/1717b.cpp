#include <iostream>
using namespace std;
 
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k, r, c;
        cin >> n >> k >> r >> c;
        int t_mod = (r + c) % k;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if ((i + j) % k == t_mod) {
                    cout << 'X';
                } else {
                    cout << '.';
                }
            }
            cout << '\n';
        }
    }
    return 0;
}
