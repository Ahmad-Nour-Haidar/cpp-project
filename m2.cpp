/*
 *
 * Ahmad Nour Haidar
 *
 * */

#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> graph;


int dfs(int root, int parent, int target) {

    if (root == target) {
        return 1;
    }
    int ans = 0;
    for (int child: graph[root]) {
        if (child not_eq parent) {
            ans += dfs(child, root, target);
        }
    }

    return ans;

}

int main() {


    int n, m;
    cin >> n >> m;
    graph.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        graph[x].emplace_back(y);
        graph[y].emplace_back(x);
    }
    int ans = 0;
    ans += dfs(1, -1, 7);
    ans += dfs(1, -1, 5);
    cout << ans << endl;

    return 0;
}
