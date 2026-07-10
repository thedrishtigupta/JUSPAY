/*
Problem
An elven ranger is navigating a tree-like network of n forest outposts, starting at the root (Outpost 1). The target destinations are secret supply caches located at the leaves of the tree.
Some outposts are monitored by enemy patrols. Each outpost i has a danger rating Ai (an integer >= 0).
When the ranger enters an outpost with patrols (Ai > 0), their Suspicion Meter increases by Ai.
When the ranger enters a completely safe outpost (Ai = 0), they can rest in the shadows, completely resetting their Suspicion Meter back to 0.
If at any point, the Suspicion Meter strictly exceeds a maximum threshold m, the ranger is spotted. The enemy locks down that outpost, meaning the ranger is captured and cannot move any further down into that subtree.
Help the ranger calculate how many secret supply caches they can safely reach.
Input Format
The first line contains two integers n and m (2 <= n <= 2 * 105, 1 <= m <= 109) — the number of outposts and the maximum allowed suspicion threshold.
The second line contains n integers A1, A2,......., An (0 <= Ai <= 106) — the danger rating of each outpost.
The next n - 1 lines each contain two integers u and v, denoting a path between outpost u and outpost v.
Output Format
Print a single integer — the total number of leaves (supply caches) the ranger can safely reach.
Sample Test Case
Input
Plaintext
5 3
1 2 0 1 2
1 2
1 3
2 4
2 5

Output: 1

TestCase2:
4 2
5 1 1 1
1 2
1 3
1 4

Output : 0

TestCase3
4 1
0 0 0 0
1 2
2 3
2 4

Output : 2

*/
#include <bits/stdc++.h>
using namespace std;

void dfs(int u, int par, vector<vector<long long>>& adj, vector<long long>& unsafe, long long& m, long long& ans, int count) {
    if(unsafe[u] == 0) count = 0;
    else count += unsafe[u];
    if (count > m) return;
    
    bool enters = false;
    
    for(auto& v : adj[u]) {
        if(v == par) continue;
        enters = true;
        dfs(v, u, adj, unsafe, m, ans, count);
    }
    if(!enters) ans++;
}

int main() {
    long long n, m;
    cin >>n>>m;
    
    vector<long long> unsafe(n+1);
    for(auto i = 1; i <= n; i++) cin>>unsafe[i];
    
    vector<vector<long long>> adj(n+1);
    
    for(auto i = 0; i < n-1; i++) {
        long long u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int count = 0;
    long long ans = 0;
    dfs(1, 0, adj, unsafe, m, ans, count);
    cout<<ans<<endl;
    

    return 0;
}