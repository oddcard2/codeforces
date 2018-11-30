#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define MAXN 100001
int c[MAXN];

int sz[MAXN];

vector<int> g[MAXN];

map<int, int> m[MAXN];
set<pair<int, int>> s[MAXN];
ll cnt[MAXN];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	//1. reads tree
	for (int i = 0; i < n; i++)
	{
		cin >> c[i+1];
	}

	for (int i = 0; i < n-1; i++)
	{
		int a, b;
		cin >> a >> b;

		g[a].push_back(b);
		g[b].push_back(a);
	}

	//2. calcs size of subtrees
	//dfs

	std::function<void(int, int)> calcsz = [&](int v, int p) {
		for (auto ch : g[v]) {
			if (ch != p)
				calcsz(ch, v);
		}
		int size = 1;
		for (auto ch : g[v]) {
			if (ch != p)
				size+=sz[ch];
		}
		sz[v] = size;
	};

	std::function<void(int, int)> solve = [&](int v, int p) {
		for (auto ch : g[v]) {
			if (ch != p)
				solve(ch, v);
		}
		//merge
		int big = -1;
		int mx = -1;
		for (auto ch : g[v]) {
			if (ch != p) {
				if (sz[ch] > mx) {
					big = ch;
					mx = sz[ch];
				}
			}
		}

		if (big != -1) {
			m[v] = move(m[big]);
			s[v] = move(s[big]);
		}
		for (auto ch : g[v]) {
			if (ch != p && ch != big) {
				for (auto it : m[ch]) {
					int color = it.first;
					int val = m[v][color];
					if (val)
						s[v].erase({ val, color });
					s[v].insert({ val + it.second, color });
					m[v][color] = val + it.second;
				}
			}
		}

		int color = c[v];
		int val = m[v][color];
		if (val)
			s[v].erase({ val, color });
		s[v].insert({ val + 1, color });
		m[v][color] = val + 1;

		//calcs answer for the subtree
		ll res = 0;
		int pval = -1;
		for (auto it = rbegin(s[v]); it != rend(s[v]); ++it) {
			if (pval == -1 || it->first == pval) {
				res += it->second;
				pval = it->first;
			}
		}
		cnt[v] = res;
	};

	calcsz(1, -1);
	solve(1, -1);

	for (int i = 0; i < n; i++)
	{
		cout << cnt[i + 1] << " ";
	}

	return 0;
}