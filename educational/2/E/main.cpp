#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define MAXN 100001
int c[MAXN];

int ids[MAXN];
int mx[MAXN];

vector<int> g[MAXN];

map<int, int> m[MAXN];
ll cnt[MAXN];
ll ans[MAXN];

void merge(int fr, int to) {
	if (m[ids[fr]].size() > m[ids[to]].size()) {
		swap(ids[fr], ids[to]);
	}

	int fid = ids[fr];
	int tid = ids[to];

	for (auto& it : m[fid]) {
		int val = m[tid][it.first] + it.second;
		m[tid][it.first] = val;

		if (val > mx[tid]) {
			cnt[tid] = 0;
			mx[tid] = val;
		}

		if (val == mx[tid]) {
			cnt[tid] += it.first;
		}
	}

};

void solve(int v, int p) {
	for (auto ch : g[v]) {
		if (ch == p)
			continue;
		solve(ch, v);
		merge(ch, v);
	}
	ans[v] = cnt[ids[v]];
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; i++)
	{
		int v = i + 1;
		cin >> c[v];
		m[v][c[v]] = 1;
		ids[v] = v;
		cnt[v] = c[v];
		mx[v] = 1;
	}

	for (int i = 0; i < n-1; i++)
	{
		int a, b;
		cin >> a >> b;

		g[a].push_back(b);
		g[b].push_back(a);
	}

	solve(1, -1);

	for (int i = 0; i < n; i++)
		cout << ans[i + 1] << " ";

	return 0;
}