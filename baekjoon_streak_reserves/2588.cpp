#ifdef _MSC_VER
#include <intrin.h>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <queue>
#include <iomanip>
#include <set>
#include <bitset>
#include <map>
#include <cstddef>
#include <chrono>
#  define __builtin_popcount __popcnt
#endif
#ifndef _MSC_VER
#  include <bits/stdc++.h>
#endif
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define OUT
#define INOUT
#define INF  0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define loop(x, n) for(int x = 0; x < n; ++ x)
#define range(x, s, e) for(int x = s; x <e; ++x)
#define all(x) (x).begin(), (x).end()
#define debug(x) cout << #x << "=" << x << '\n'
#define debugv(v) cout << #v << ":"; for(auto i:v) cout << i << " "; cout << endl;
#define FIXED_FLOAT(n, x) fixed <<setprecision(n)<<(x)

using namespace std;
using ll = long long;
using uint = unsigned int;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vector<int>>;
using vvl = vector < vector < ll >>;
using p3i = tuple<int, int, int>;
using p5l = tuple<ll, ll, ll, ll, ll>;
using p3l = tuple<ll, ll, ll>;


int coins[101];
int dp[101][10001];
int main() {
    //fastio;
    int N, K;
    cin >> N >> K;
    range(c, 1, N+1) {
        cin >> coins[c];
    }
    fill(dp[0]+1, dp[0] + 10001, INF);
    for (int i = 1; i <= N; ++i) {
        //considering up to ith coin
        for (int s = 0; s <= K; ++s) {
            dp[i][s] = dp[i - 1][s];
            if (s - coins[i] >= 0 && dp[i][s - coins[i]] != INF) dp[i][s] = min(dp[i][s], 1 + dp[i][s - coins[i]]);
        }
    }
    if (dp[N][K] != INF) {
        cout << dp[N][K] << endl;
    }
    else {
        cout << -1 << endl;
    }

    return 0;
}
