#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

vector<int> used;
vector<vector<int>> g;

int d = 0;

//depth
int l1cnt = 0;
vector<vector<int>> leafs;
vector<vector<int>> timev;

function<void(int)> dfs = [&](int v) {
	used[v] = 1;
	
	int cd = d++;

	if (cd == 1) {
		leafs.push_back({});
	}

	int leaf = 1;
	for (auto u : g[v]) {
		if (used[u])
			continue;

		dfs(u);
		leaf = 0;
	}
	if (leaf) {
		leafs[l1cnt].push_back(cd-1);
	}
	if (cd == 1) {
		l1cnt++;
	}
	--d;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	g.resize(n);
	used.resize(n);

	for (int i = 0; i < n-1; i++)
	{
		int v, u;
		cin >> v >> u; 
		--v;
		--u;

		g[v].push_back(u);
		g[u].push_back(v);
	}

	dfs(0);

	timev.resize(leafs.size());

	int cnt = 0;
	int mx = 0;
	for (auto& vv : leafs) {
		sort(begin(vv), end(vv));

		timev[cnt].resize(vv.size());
		timev[cnt][0] = vv[0];
		for (int i = 1; i < vv.size(); i++)
		{
			timev[cnt][i] = max(vv[i], timev[cnt][i - 1] + 1);
		}
		mx = max(mx, timev[cnt][vv.size() - 1]);
		cnt++;
	}

	cout << mx+1;

	return 0;
}