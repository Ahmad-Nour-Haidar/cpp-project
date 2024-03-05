#include <bits\stdc++.h>

using namespace std;
int a[1000];
int index = 0;

void generateLuckyNumber(int number, int endNumber) {
    if (number > endNumber) {
        return;
    }
    a[index] = number;
    index++;
    generateLuckyNumber(number * 10 + 4, endNumber);
    generateLuckyNumber(number * 10 + 7, endNumber);
}

int main() {

    generateLuckyNumber(0, 100000);
    sort(a, a + index);
    for (int i = 1; i < index; ++i) {
        cout << a[i] << ' ';
    }

    return 0;
}

// 4 7 44 47 74 77 444 447 474 477 744 747 774 777 4444 4447 4474 4477 4744 4747 4774 4777 7444 7447 7474 7477 7744 7747
// 7774 7777 44444 44447 44474 44477 44744 44747 44774 44777 47444 47447 47474 47477 47744 47747 47774 47777 74444 74447
// 74474 74477 74744 74747 74774 74777 77444 77447 77474 77477 77744 77747 77774 77777