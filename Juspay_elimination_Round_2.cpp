
/*
Limak is studying an interactive gaming platform where two players can form alliances, which allows them to chat and share gaming strategies.

The platform has n players, each distinguished by a unique number from 1 to n. Currently, there are m pairs of players who have formed alliances. It's understood that a player cannot form an alliance with themselves.

If players A and B are allies, it's represented as A-B. Limak believes a gaming platform is orderly only if it satisfies this rule: For any three unique players (X, Y, Z), if X is allies with Y and Y is allies with Z, then X must also be allies with Z.

For example, if Alex is allies with Ben, and Ben is allies with Chris, then Alex must be allies with Chris.

Can you help Limak determine if the gaming platform adheres to this rule? If it does, output "YES"; if it doesn't, output "NO".

Input:
The first line of the input will contain two integers n and m (3 ≤ n ≤ 150 000, ) representing the total number of players and the number of allied pairs.

Each of the subsequent m lines will contain two distinct integers ai and bi (1 ≤ ai, bi ≤ n, ai ≠ bi) representing players who have formed an alliance. Each allied pair will be unique in the input.

Output:
If the gaming platform adheres to the rule, output "YES"; if it does not, output "NO".

Input:
4 3
1 3
3 4
1 4

Output: YES

Input:
4 4
3 1
2 3
3 4
1 2

Output: NO
*/
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, m; cin>>n>>m;

    unordered_map<int, vector<int>> adj;

    for(int i = 0; i < m; i++) {
        int a, b; cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<bool>visited(n, false);

    bool ans = true;

    for(int i = 1; i <= n; i++) {
        if(!visited[i]) {
            int nodes = 0;
            int edges = 0;
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while(!q.empty()) {
                int node  = q.front(); q.pop();

                nodes++;
                edges += adj[node].size();

                for(int v : adj[node]) {
                    if(!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            int expected = nodes*(nodes-1) / 2;
            int actual = edges/2;
            if(actual != expected) {ans = false; break;}
        }
        
    }
    if(ans) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}