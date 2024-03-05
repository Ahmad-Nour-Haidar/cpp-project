#include <bits/stdc++.h>

using namespace std;

// Ahmad Nour Haidar
class Solution {
public:
    int minimumLength(const string &s) {
        int len = s.length();
        if (len == 1)return 1;
        int l = 0, r = len - 1, c = 0;
        while (l < r) {
            if (s[l] == s[r]) {
                l++;
                r--;
                c += 2;
            } else if (l > 0 and s[l] == s[l - 1]) {
                l++;
                c++;
            } else if (r < len and s[r] == s[r + 1]) {
                r--;
                c++;
            } else break;
        }
        if ((len & 1) and (len - c) == 1 and s[(len / 2)] == s[(len / 2) - 1])c++;
        return len - c;
    }
};

int main() {
    int a[123] = {};
    for (auto it :a)cout << it << endl;
    return 0;
}
