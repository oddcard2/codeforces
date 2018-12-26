#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<ll> vll;

typedef pair<int, int> pii;
typedef tuple<int, int, int> tri;

/***********************/
struct seg_tree {
	struct node { ///
		int val;
		int ad = 0;

		//assigns new value to the segment node
		void apply(int tl, int tr, int v) {
			ad += v;
			val += v * (tr - tl + 1);
		}
	};

	node unite(const node &a, const node &b) const {
		node res;
		res.val = a.val + b.val;
		return res;
	}

	void push(int v, int tl, int tr) { ///
		if (tree[v].ad != 0) {
			int tm = (tl + tr) / 2;
			tree[v * 2].apply(tl, tm, tree[v].ad);
			tree[v * 2 + 1].apply(tm + 1, tr, tree[v].ad);
			tree[v].ad = 0;
		}
	}

	void pull(int v) { //combines results from sons to parent
		tree[v] = unite(tree[v * 2], tree[v * 2 + 1]);
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
			tree[v].apply(tl, tr, a[tl]);
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
		push(v, tl, tr);
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
			tree[v].apply(tl, tr, d...);
		else {
			push(v, tl, tr);
			int tm = (tl + tr) / 2;
			if (l <= tm)
				update(v * 2, tl, tm, l, r, d...);
			if (r > tm)
				update(v * 2 + 1, tm + 1, tr, l, r, d...);
			pull(v);
		}
	}

	template <typename... M>
	void update_range(int l, int r, const M&... v) {
		update(1, 0, n - 1, l, r, v...);
	}

	template <typename... M>
	void update(int pos, const M&... v) {
		update(1, 0, n - 1, pos, pos, v...);
	}

	int n;
	vector<node> tree;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	vector<pair<int, int>> lr(n);

	vector<tri> v(2*n);

	int j = 0;
	for (int i = 0; i < n; i++)
	{
		int l, r;
		cin >> l >> r;
		lr[i] = { l,r };
		v[j++] = { l, i, 0 };
		v[j++] = { r, i, 1 };
	}

	sort(begin(v), end(v));

	vector<int> b(4*n);

	int na = 0;
	int preva = -1;
	for (int i = 0; i < 2*n; i++)
	{
		int a, m, s;
		tie(a,m,s) = v[i];

		if (i > 0 && a != preva) {
			na+=2;
		}
		preva = a;

		b[na] = a;

		if (s == 0)
			lr[m].first = na;
		else
			lr[m].second = na;

	}

	vector<int> vv(na+1);

	/***********************/
	seg_tree t;
	t.build(vv);

	/***********************/

	for (int i = 0; i < n; i++)
	{
		t.update_range(lr[i].first, lr[i].second, 1);
	}

	for (int i = 0; i < na+1; i++) {
		vv[i] = t.get(i).val;
	}

	vector<pii> res;
	int l = -1, r;
	for (int i = 0; i < na+2; i++)
	{
		if (i == na + 1) {
			if (l != -1) {
				res.push_back({ l,r });
			}
			break;
		}
		if (vv[i] >= k) {
			if (l == -1) {
				l = i;
				r = i;
			}
			else {
				r++;
			}
		}
		else {
			if (l != -1) {
				res.push_back({ l,r });
				l = -1;
			}
		}
	}

	cout << res.size() << '\n';
	for (int i = 0; i < res.size(); i++)
	{
		cout << b[res[i].first] << " " << b[res[i].second] << '\n';
	}

	return 0;
}