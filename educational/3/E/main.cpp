#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

class dsu
{
public:
	dsu(int n);
	void reinit_dsu(int n);
	void make(int r);
	int find(int elem);
	int unite(int s1, int s2);
private:
	std::vector<int> parent;
	std::vector<int> rank;
};

dsu::dsu(int n)
{
	reinit_dsu(n);
}

void dsu::reinit_dsu(int n)
{
	parent.resize(n);
	rank.resize(n);
}

void dsu::make(int r)
{
	parent[r] = r;
	rank[r] = 1;
}

int dsu::find(int elem)
{
	if (parent[elem] == elem)
		return elem;
	parent[elem] = find(parent[elem]);
	return parent[elem];
}

int dsu::unite(int s1, int s2)
{
	s1 = find(s1);
	s2 = find(s2);

	//from s1 to s2
	if (rank[s2] < rank[s1])
		std::swap(s1, s2);

	parent[s1] = s2;
	if (rank[s1] == rank[s2])
		rank[s2]++;
	return s2;
}

int n;
vector<vector<pair<int, int>> > g;
vector<tuple<int, int, int, ll>> edges;
vector<ll> sums;
vector<int> ids;
vector<int> ans;

ll mst_kruskal() {
	ll sum = 0;
	//sort edges
	sort(begin(edges), end(edges), [](const tuple<int, int, int, ll>& a, const tuple<int, int, int, ll>& b) { return get<3>(a) < get<3>(b); });

	dsu d(n);
	for (int i = 0; i < n; i++)
	{
		d.make(i);
	}

	for (int i = 0; i < edges.size(); i++) {
		int j, u, v, w;
		tie(j, u, v, w) = edges[i];

		if (d.find(u) != d.find(v)) {
			d.unite(u, v);
			ans.push_back(j);
			sum += w;
		}

		ids[j] = i;
	}

	for (int i = 0; i < ans.size(); i++)
	{
		sums[ans[i]] = sum;
	}
	return sum;
}

int l;
vector<int> tin, tout;
vector<vector<int> > up;
vector<vector<int> > md;
vector<int> vh;
vector<ll> pw;
int timer = 0;

void bl_dfs(int v, int p = 0) {
	tin[v] = ++timer;

	up[v][0] = p;
	
	//premature optimization is the root of all evil:
	for (int i = 1; i <= l /*&& up[v][i - 1] > 0*/; ++i) {
		up[v][i] = up[up[v][i - 1]][i - 1];
		md[v][i] = max(md[v][i - 1], md[up[v][i - 1]][i - 1]);
	}

	for (int j = 0; j < g[v].size(); ++j) {
		int u = g[v][j].first;
		if (u == p)
			continue;

		pw[u] = g[v][j].second;
		md[u][0] = g[v][j].second;
		vh[u] = vh[v] + 1;
		bl_dfs(u, v);
	}
	tout[v] = ++timer;
}

bool upper(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int get_best(int v, int span)
{
	int ret = numeric_limits<int>::min();
	for (int i = l; i >= 0; --i)
	{
		if (span&(1 << i))
		{
			ret = max(ret, md[v][i]);
			v = up[v][i];
		}
	}
	return ret;
}

int lca(int a, int b) {
	if (upper(a, b))
		return a;

	if (upper(b, a))
		return b;

	int u = a;
	int i = l;

	do {
		if (!upper(up[u][i], b))
			u = up[u][i];
		--i;
	} while (i >= 0);
	return up[u][0];
}

void init_lca(int n) {
	tin.resize(n), tout.resize(n), up.resize(n);
	md.resize(n);
	vh.resize(n);
	l = 1;
	while ((1 << l) <= n)  ++l;
	for (int i = 0; i < n; ++i) {
		up[i].resize(l + 1);
		md[i].resize(l + 1);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int m;
	cin >> n >> m;

	g.resize(n);

	sums.resize(m, -1);
	edges.resize(m);
	ids.resize(m);
	for (int i = 0; i < m; i++)
	{
		int u, v;
		ll w;
		cin >> u >> v >> w;
		u--;
		v--;

		edges[i] = {i, u, v, w};
	}

	init_lca(n);

	ll s = mst_kruskal();

	pw.resize(n);

	int root = get<1>(edges[ids[ans[0]]]);
	for (int i = 0; i < ans.size(); i++)
	{
		int j, u, v;
		ll w;
		tie(j, u, v, w) = edges[ids[ans[i]]];

		g[u].push_back({ v,w });
		g[v].push_back({ u, w });
	}

	bl_dfs(0);

	for (int i = 0; i < m; i++)
	{
		if (sums[i] == -1) {
			int j, u, v, w;
			tie(j, u, v, w) = edges[ids[i]];

			int lc, mx;
			lc = lca(u, v);
			mx = max(get_best(u, vh[u] - vh[lc]), get_best(v, vh[v] - vh[lc]));
			
			sums[i] = s + w - mx;
		}
	}

	for (int i = 0; i < sums.size(); i++)
	{
		cout << sums[i] << '\n';
	}
	return 0;
}