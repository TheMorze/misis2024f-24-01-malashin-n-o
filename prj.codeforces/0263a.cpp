#include <iostream>
 
int main() {
    int posi, posj;
    int a[5][5];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            std::cin >> a[i][j];
            if (a[i][j] == 1) {
                posi = i;
                posj = j;
            }
        }
    }
    int res = 0;
    while (posi != 2 or posj != 2) {
        while (posi < 2) {
            res += 1;
            posi += 1;
        }
        while (posi > 2) {
            res += 1;
            posi -= 1;
        }
        while (posj < 2) {
            res += 1;
            posj += 1;
        }
        while (posj > 2) {
            res += 1;
            posj -= 1;
        }
    }
    std::cout << res;
}
 
