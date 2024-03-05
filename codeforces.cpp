/**
 *
 * Ahmad Nour Haidar
 *
 **/
#include <bits/stdc++.h>

using namespace std;
#define FILE freopen("input.txt", "r", stdin) , freopen("output.txt", "w", stdout)
#define cin_cout ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define testCases int TestCases; cin >> TestCases; while (TestCases--)
#define log(x) (31^__builtin_clz(x)) // Time complexity : O(log2(x))
const long double pi = 3.14159265358979323846;
#define _mid(l, r) ((l) + ((r - l) >> 1));
#define printAns(ans) cout << ans << '\n'
#define rall(a) a.rbegin(), a.rend()
#define all(a) a.begin(), a.end()
#define new_line cout << "\n"
#define YES cout << "YES\n"
#define NO cout << "NO\n"
typedef long long ll;
#define space ' '
#define endl '\n'
#define not_ ~
#define Mod (int)(1e9 + 7)

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
    cin_cout;
    int a[123] = {};
    for (auto it :a)cout << it << endl;
    return 0;
}
