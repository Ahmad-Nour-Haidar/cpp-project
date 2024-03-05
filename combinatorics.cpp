#include <bits/stdc++.h>

using namespace std;
#define testCases int TestCases; cin >> TestCases; while (TestCases--)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define endl '\n'
#define space ' '
#define Mod (int)(1e9 + 7)
#define not_ ~
#define NO cout << "NO\n"
#define YES cout << "YES\n"
#define new_line cout << "\n"
#define printAns(ans) cout << ans << '\n'
#define cin_cout ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr)
#define FILE freopen("input.txt", "r", stdin) , freopen("output.txt", "w", stdout)
typedef long long ll;
//const double pi = 3.1415926536;


/// combinatorics
#define sizeArray (int)(1e6 + 3)

ll mod(ll x) {
    return (x % Mod);
}

int multi(ll x, ll y) {
    return mod(mod(x) * mod(y));
}

//  x^n
ll powerWithMod(ll x, ll n) {
    ll result = 1;
    while (n) {
        if (n & 1) {
            result = result * x;
            result = mod(result);
        }
        x = multi(x, x);
        n >>= 1;
    }
    return result;
}

ll modInverse(ll a) {
    return powerWithMod(a, Mod - 2);
}

int fact[sizeArray];

void fillFact() {
    fact[0] = 1;
    for (int i = 1; i < sizeArray; ++i) {
        fact[i] = multi(fact[i - 1], i);
    }
}

ll combinatorics(ll n, ll r) {
    return multi(multi(fact[n], modInverse(fact[r])), modInverse(fact[n - r]));
}

int main() {

    fillFact();
    cout << combinatorics(7, 3);

    return 0;
}