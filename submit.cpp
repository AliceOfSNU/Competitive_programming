#include <bits/stdc++.h>
#define fastio std::ios_base::sync_with_stdio(0); std::cin.tie(0); std::cout.tie(0);
using namespace std;
using pii = pair<int, int>;
using vi = vector<int>;
using ll = long long;
using vvi = vector<vi>;

int N, M;
vector<int> costs;
vector<vector<pii>> G;
int main(){
    fastio;
    cin >> N >> M;
    G.resize(N+1);
    costs.resize(N+1);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    for(int i = 1; i <= N; ++i){
        cin >> costs[i];
        pq.emplace(costs[i], i);
    }
    int R; cin >> R;
    for(int r = 0; r < R; ++r){
        int a, b, c; cin >> a >> b >> c;
        G[a].emplace_back(b, c);
    }
    
    int answer = 0;
    while(M--){
        int cost, node;
        tie(cost, node) = pq.top(); pq.pop();
        if(costs[node] != cost) continue;
        answer = max(answer, cost);
        for(pii &p : G[node]){//deal with discounts
            int n, dc; tie(n, dc) = p;
            costs[n] -= dc;
            pq.emplace(costs[n], n);
        }
    }
    cout << answer << endl;
    return 0;
}

//test case
/*
3 3
10 20 30
0
OUTPUT: 30

3 3
10 20 30
3
1 2 10
1 3 10
2 3 10
OUTPUT 10
*/
