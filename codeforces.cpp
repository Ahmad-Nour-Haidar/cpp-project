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

int main() {
    cin_cout;

    testCases {
        int n;
        cin >> n;
        int a[n];
        for (int &i:a)cin >> i;
        bool ans = true;
        for (int i = 1; i < n - 1 and ans; ++i) {
            a[i] -= (2 * a[i - 1]);
            a[i + 1] -= a[i - 1];
            a[i - 1] -= a[i - 1]; // = 0
            ans &= (a[i] >= 0);
        }
        // check
        if (ans) for (auto it :a)ans &= (it == 0);
        ans ? YES : NO;
    };

    return 0;
}
