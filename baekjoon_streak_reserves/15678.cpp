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


ll dp[100'000];
//dp[i] = max score ending at spot
//dp[i] = max(i-D <= j < i)dp[j] -> uses monotone queue
vi arr;
int main() {
    fastio;
    int N, D;
    cin >> N >> D;
    arr.resize(N);
    loop(i, N) cin >> arr[i];

    deque<int> steps;
    dp[0] = arr[0];//init
    ll answer = dp[0];
    steps.push_back(0);

    for (int i = 1; i < N; ++i) {
        while (steps.size() && steps.front() < i - D) steps.pop_front(); //discard old items
        dp[i] = arr[i] + max((ll)0, dp[steps.front()]);
        while (steps.size() && dp[steps.back()] < dp[i]) steps.pop_back(); //steps may become empty
        steps.push_back(i);

        answer = max(dp[i], answer);
    }

    cout << answer << endl;
    return 0;
}
