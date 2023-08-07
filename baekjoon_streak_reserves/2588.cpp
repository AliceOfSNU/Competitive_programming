//for MSVC compiler.
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
#  define __builtin_popcount __popcnt
#endif
#ifndef _MSC_VER
#  include <bits/stdc++.h>
#endif
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
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
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vector<int>>;
using vvl = vector < vector < ll >>;
using p3i = tuple<int, int, int>;
using p4i = tuple<int, int, int, int>;
using p3l = tuple<ll, ll, ll>;
using uint = unsigned int;


//MIND INTEGER OVERFLOW
int N, Q;
int dp[500'000];
int addtree[1'000'002], subtree[1'000'002];


int range_max(int* segtree, int node, int l, int r, int ql, int qr) {
	if (r < ql || l > qr) return 0;
	if (ql <= l && r <= qr) return segtree[node];
	int mid = (l + r) / 2;
	return max(range_max(segtree, node * 2, l, mid, ql, qr), range_max(segtree, node * 2 + 1, mid + 1, r, ql, qr));
}

int point_update(int* segtree, int  node, int l, int r, int w, int val) {
	if (w < l || w >r) return segtree[node];
	if (l == w && r == w) { segtree[node] = max(segtree[node], val); return segtree[node]; }

	int mid = (l + r) / 2;
	return segtree[node] = max(point_update(segtree, 2 * node, l, mid, w, val), point_update(segtree, 2 * node + 1, mid + 1, r, w, val));
}

int main(int argc, char* argv[])
{
	fastio;
	cin >> N >> Q;
	vi idxs(N); vector<pii> pos(N);
	vi sv, av; sv.reserve(N), av.reserve(N);

	//srand(11);
	//loop(i, Q) {
	//	int s = rand() % N, e = rand() % N, v = rand() % 200, w = rand() % N;
	//	assert(range_max(addtree, 1, 0, N-1, min(s,e), max(s,e)) == *max_element(idxs.begin()+min(s,e), idxs.begin()+max(s,e)+1));
	//	idxs[w] = max(idxs[w], v);
	//	point_update(addtree, 1, 0, N - 1, w, v);
	//}
	loop(i, N) {
		cin >> pos[i].first >> pos[i].second;
		sv.push_back(pos[i].first - pos[i].second);
		av.push_back(pos[i].first + pos[i].second);
	}

	sort(all(sv));//worst 1e6 nlogn
	sort(all(av));
	sv.erase(unique(all(sv)), sv.end());
	av.erase(unique(all(av)), av.end());

	iota(all(idxs), 0);
	sort(all(idxs), [&](int i, int j)-> bool { return pos[i].second < pos[j].second; });

	const int sz = sv.size(), az = av.size();

	loop(i, N) {//from lowest point going up..
		int x, y; tie(x, y) = pos[idxs[i]];
		int addi = lower_bound(all(av), x + y) - av.begin(), subi = lower_bound(all(sv), x - y) - sv.begin(); //LOGN
		int best = max(range_max(addtree, 1, 0, az - 1, addi, az - 1), range_max(subtree, 1, 0, sz - 1, 0, subi));
		dp[idxs[i]] = ++best; //including this point!

		point_update(addtree, 1, 0, az - 1, addi, best);
		point_update(subtree, 1, 0, sz - 1, subi, best);
	}

	loop(i, Q) {
		int q; cin >> q;
		cout << dp[q - 1] << "\n";
	}
	return 0;

}