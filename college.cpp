

/// Ahmad Nour Haidar

#include <bits/stdc++.h>

// FORWARD AND BACKWARD NEWTON-GREGORY METHODS

using namespace std;

#define endl '\n'
#define type  double
#define w  6

void forward_newton_gregory(const type *x, const type *y, int n, int degree, int degree_function, type calc_value) {
    vector<int> fact(17);
    fact[0] = 1;
    fact[1] = 1;
    for (int i = 2; i < 17; ++i) {
        fact[i] = (fact[i - 1] * i);
    }
//    for (int i = 0; i < 17; ++i) {
//        cout << fact[i] << endl;
//    }
    vector<vector<type> > a(n);
    for (int i = 0; i < n; ++i) {
        a[i].emplace_back(y[i]);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            a[j].emplace_back(a[j][i] - a[j - 1][i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (auto it:a[i]) {
            cout << setprecision(w) << it << ' ';
        }
        cout << endl;
    }
    vector<type> delta(n);
    for (int i = 0; i < n; ++i) {
        delta[i] = a[i][i];
    }
    vector<type> values_p(n);
    values_p[0] = 1;
    values_p[1] = (calc_value - x[0]) / (x[1] - x[0]);
    for (int i = 2; i <= degree; ++i) {
        values_p[i] = values_p[i - 1];
        values_p[i] *= (values_p[1] - (i - 1));
    }
    type ans = 0;
    for (int i = 0; i <= degree_function; ++i) {
        ans += (delta[i] * values_p[i] / (type) fact[i]);
    }
    cout << "P (" << calc_value << ") = " << setprecision(w) << ans << endl;
    if (degree_function < degree) {
        type error = abs(delta[degree_function + 1] * values_p[degree_function + 1] / (type) fact[degree_function + 1]);
        cout << "E (" << calc_value << ") = " << fixed << setprecision(w)
             << error << endl;
    }
}

void backword_newton_gregory(const type *x, const type *y, int n, int degree, int degree_function, type calc_value) {
    vector<int> fact(17);
    fact[0] = 1;
    fact[1] = 1;
    for (int i = 2; i < 17; ++i) {
        fact[i] = (fact[i - 1] * i);
    }
//    for (int i = 0; i < 17; ++i) {
//        cout << fact[i] << endl;
//    }
    vector<vector<type> > a(n);
    for (int i = 0; i < n; ++i) {
        a[i].emplace_back(y[i]);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            a[j].emplace_back(a[j][i] - a[j - 1][i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (auto it:a[i]) {
            cout << setprecision(w) << it << ' ';
        }
        cout << endl;
    }
    vector<type> delta(n);
    for (int i = 0; i < n; ++i) {
        delta[i] = a[n - 1][i];
    }
//    for (int i = 0; i < n; ++i) {
//        cout << delta[i] << ' ';
//    }
//    cout << endl;
    vector<type> values_s(n);
    values_s[0] = 1;
    values_s[1] = (calc_value - x[n - 1]) / (x[n - 1] - x[n - 2]);
    for (int i = 2; i <= degree; ++i) {
        values_s[i] = values_s[i - 1];
        values_s[i] *= (values_s[1] + (i - 1));
    }
    type ans = 0;
    for (int i = 0; i <= degree_function; ++i) {
        ans += (delta[i] * values_s[i] / (type) fact[i]);
    }
    cout << "P (" << calc_value << ") = " << setprecision(w) << ans << endl;
    if (degree_function < degree) {
        type error = abs(delta[degree_function + 1] * values_s[degree_function + 1] / (type) fact[degree_function + 1]);
        cout << "E (" << calc_value << ") = " << fixed << setprecision(w)
             << error << endl;
    }
}

void initial() {
    // array values x:
    type x[] = {0, 0.2, 0.4, 0.6, 0.8, 1};

    // array values y:
    type y[] = {0, 0.203, 0.423, 0.684, 1.030, 1.557};

    // number values:
    int n = sizeof(x) / sizeof(x[0]);

    int degree = n - 1;
    int degree_function = 3;

    type calc_value = 0.73;
//    forward_newton_gregory(x, y, n, degree, degree_function, calc_value);
    cout << "=====================================\n";
    backword_newton_gregory(x, y, n, degree, degree_function, calc_value);

}


int main() {

    initial();


    return 0;
}

// 0.4978706837 0.2231301601 1 4.48168907 20.08553692
// 0.0 0.203 0.423 0.684 1.030 1.557
// 0.72999999999999998



//    type qq = delta[degree_function + 1];
//    type ww = values_s[degree_function + 1];
//    type ee = (type) fact[degree_function + 1];
//    cout << qq << endl;
//    cout << ww << endl;
//    cout << ee << endl;
//    v1 = qq * ww;
//    v2 = v1 / ee;
//    cout << setprecision(15) << v2 << endl;
//    cout << setprecision(15) << qq * ww / ee << endl;