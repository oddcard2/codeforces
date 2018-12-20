#include "bits/stdc++.h"

using namespace std;

typedef long long ll;
typedef uint64_t ull;
typedef uint64_t i64;

//http://e-maxx.ru/algo/segment_tree
//with modifications
/***********************/
struct seg_tree {
	struct node { ///
		int lazy = 0;
		int color;

		uint64_t mask;

		//assigns new value to the segment node
		void apply(int col) {
			lazy = 1;
			color = col;
			mask = (1ull << col);
		}
	};

	node unite(const node &a, const node &b) const {
		node res;
		res.mask = a.mask | b.mask;
		return res;
	}

	void push(int v) { ///
		if (tree[v].lazy) {
			tree[2 * v].apply(tree[v].color);
			tree[2 * v + 1].apply(tree[v].color);
			tree[v].lazy = 0;
		}
	}

	//after modification of sons
	void pull(int v) { //combines results from sons to parent
		tree[v].mask = tree[v * 2].mask | tree[v * 2 + 1].mask;
	}

	template<typename T>
	void build(const vector<T>& a) {
		n = (int)a.size();
		tree.resize(4 * n);
		build(1, 0, n - 1, a);
	}

	template<typename T>
	void build(int v, int tl, int tr, const vector<T>& a) {
		if (tl == tr)
			tree[v].apply(a[tl]);
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm, a);
			build(v * 2 + 1, tm + 1, tr, a);
			pull(v);
		}
	}

	node get(int v, int tl, int tr, int l, int r) {
		if (l <= tl && r >= tr) {
			return tree[v];
		}
		push(v);
		node res{};
		int tm = (tl + tr) / 2;

		if (r <= tm) {
			res = get(2 * v, tl, tm, l, r);
		}
		else {
			if (l > tm) {
				res = get(2 * v + 1, tm + 1, tr, l, r);
			}
			else {
				res = unite(get(2 * v, tl, tm, l, r), get(2 * v + 1, tm + 1, tr, l, r));
			}
		}
		pull(v);
		return res;
	}


	node get(int l, int r) {
		return get(1, 0, n - 1, l, r);
	}

	node get(int pos) {
		return get(1, 0, n - 1, pos, pos);
	}

	//v - current tree node
	//l,r - required range
	//tl,tr - current tree node range
	template <typename... M>
	void update(int v, int tl, int tr, int l, int r, const M&... d) {
		if (l > r)
			return;
		if (l <= tl && r >= tr)
			tree[v].apply(d...);
		else {
			push(v);
			int tm = (tl + tr) / 2;
			if (l <= tm)
				update(v * 2, tl, tm, l, r, d...);
			if (r > tm)
				update(v * 2 + 1, tm + 1, tr, l, r, d...);
			pull(v);
		}
	}

	template <typename... M>
	void update(int l, int r, const M&... v) {
		update(1, 0, n - 1, l, r, v...);
	}

	template <typename... M>
	void update(int pos, const M&... v) {
		update(1, 0, n - 1, pos, pos, v...);
	}

	int n;
	vector<node> tree;
};

/***********************/

struct range { ///
	int s;
	int e;
};
vector<range> vertex_range; ///

vector<int> used;
vector<vector<int>> g;
int timer = -1;

function<void(int)> dfs = [&](int v) {
	used[v] = 1;

	vertex_range[v].s = ++timer;

	for (auto u : g[v]) {
		if (used[u])
			continue;

		dfs(u);
	}
	vertex_range[v].e = timer;
};

int bit_count(uint64_t v) {
	return std::bitset<64>(v).count();
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);


	int n, m;
	cin >> n >> m;

	/***********************/
	g.resize(n);
	vertex_range.resize(n);
	used.resize(n);
	/***********************/

	vector<int> c(n);
	for (int i = 0; i < n; i++)
	{
		cin >> c[i];
	}

	for (int i = 0; i < n-1; i++) {
		int v,u;
		cin >> v >> u;
		--v; --u;

		g[v].push_back(u);
		g[u].push_back(v);
	}

	dfs(0);

	vector<int> colors_tree(n);

	for (int i = 0; i < n; i++) {
		colors_tree[vertex_range[i].s] = c[i];
	}

	seg_tree tr;
	tr.build(colors_tree);

	//requests processing
	for (int i = 0; i < m; i++)
	{
		int t;
		cin >> t;
		if (t == 1) {
			int v, cc;
			cin >> v >> cc;
			v--;

			tr.update(vertex_range[v].s, vertex_range[v].e, cc);
		}
		else {
			int v;
			cin >> v;
			v--;

			seg_tree::node q = tr.get(vertex_range[v].s, vertex_range[v].e);
			cout << bit_count(q.mask) << '\n';

			//cout << "**********\n";
			//for (int i = 0; i < n; ++i) {
			//	cout << tr.get(i).color << " ";
			//}
			//cout << "**********\n";

		}
	}
	return 0;
}