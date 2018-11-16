#define _CRT_SECURE_NO_WARNINGS
#include "bits/stdc++.h"

using namespace std;

typedef int64_t i64;

class segtree {
public:
	struct node {
		i64 count = 0;
		i64 sum = 0;
		void apply(int l, int r, i64 v) {
			sum += v;
			if (v < 0)
				count--;
			else if (v > 0)
				count++;
		}
	};
	node unite(const node &a, const node &b) const {
		node res;
		res.sum = a.sum + b.sum;
		res.count = a.count + b.count;
		return res;
	}

	inline void push(int x, int l, int r) {
	}

	inline void pull(int x, int z) {
		tree[x] = unite(tree[x + 1], tree[z]);
	}

	int n;
	vector<node> tree;

	void build(int x, int l, int r) {
		if (l == r) {
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		build(x + 1, l, y);
		build(z, y + 1, r);
		pull(x, z);
	}

	template <typename M>
	void build(int x, int l, int r, const vector<M> &v) {
		if (l == r) {
			tree[x].apply(l, r, v[l]);
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		build(x + 1, l, y, v);
		build(z, y + 1, r, v);
		pull(x, z);
	}

	node get(int x, int l, int r, int ll, int rr) {
		if (ll <= l && r <= rr) {
			return tree[x];
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		push(x, l, r);
		node res{};
		if (rr <= y) {
			res = get(x + 1, l, y, ll, rr);
		}
		else {
			if (ll > y) {
				res = get(z, y + 1, r, ll, rr);
			}
			else {
				res = unite(get(x + 1, l, y, ll, rr), get(z, y + 1, r, ll, rr));
			}
		}
		pull(x, z);
		return res;
	}

	template <typename... M>
	void modify(int x, int l, int r, int ll, int rr, const M&... v) {
		if (ll <= l && r <= rr) {
			tree[x].apply(l, r, v...);
			return;
		}
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		push(x, l, r);
		if (ll <= y) {
			modify(x + 1, l, y, ll, rr, v...);
		}
		if (rr > y) {
			modify(z, y + 1, r, ll, rr, v...);
		}
		pull(x, z);
	}

	int find_first_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
		if (l == r) {
			return l;
		}
		push(x, l, r);
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		int res;
		if (f(tree[x + 1])) {
			res = find_first_knowingly(x + 1, l, y, f);
		}
		else {
			res = find_first_knowingly(z, y + 1, r, f);
		}
		pull(x, z);
		return res;
	}

	int find_first(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
		if (ll <= l && r <= rr) {
			if (!f(tree[x])) {
				return -1;
			}
			return find_first_knowingly(x, l, r, f);
		}
		push(x, l, r);
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		int res = -1;
		if (ll <= y) {
			res = find_first(x + 1, l, y, ll, rr, f);
		}
		if (rr > y && res == -1) {
			res = find_first(z, y + 1, r, ll, rr, f);
		}
		pull(x, z);
		return res;
	}

	int find_last_knowingly(int x, int l, int r, const function<bool(const node&)> &f) {
		if (l == r) {
			return l;
		}
		push(x, l, r);
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		int res;
		if (f(tree[z])) {
			res = find_last_knowingly(z, y + 1, r, f);
		}
		else {
			res = find_last_knowingly(x + 1, l, y, f);
		}
		pull(x, z);
		return res;
	}

	int find_last(int x, int l, int r, int ll, int rr, const function<bool(const node&)> &f) {
		if (ll <= l && r <= rr) {
			if (!f(tree[x])) {
				return -1;
			}
			return find_last_knowingly(x, l, r, f);
		}
		push(x, l, r);
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);
		int res = -1;
		if (rr > y) {
			res = find_last(z, y + 1, r, ll, rr, f);
		}
		if (ll <= y && res == -1) {
			res = find_last(x + 1, l, y, ll, rr, f);
		}
		pull(x, z);
		return res;
	}

	segtree(int _n) : n(_n) {
		assert(n > 0);
		tree.resize(2 * n - 1);
		build(0, 0, n - 1);
	}

	template <typename M>
	segtree(const vector<M> &v) {
		n = v.size();
		assert(n > 0);
		tree.resize(2 * n - 1);
		build(0, 0, n - 1, v);
	}

	node get(int ll, int rr) {
		assert(0 <= ll && ll <= rr && rr <= n - 1);
		return get(0, 0, n - 1, ll, rr);
	}

	node get(int p) {
		assert(0 <= p && p <= n - 1);
		return get(0, 0, n - 1, p, p);
	}

	template <typename... M>
	void modify(int ll, int rr, const M&... v) {
		assert(0 <= ll && ll <= rr && rr <= n - 1);
		modify(0, 0, n - 1, ll, rr, v...);
	}

	int get_pos_less(int x, int l, int r, i64& limit) {
		int y = (l + r) >> 1;
		int z = x + ((y - l + 1) << 1);

		if (l == r && tree[x].sum > limit) {
			return l;
		}

		if (tree[x+1].sum <= limit) {
			limit -= tree[x + 1].sum;
		}
		else {
			return get_pos_less(x + 1, l, y, limit);
		}

		if (tree[z].sum <= limit)
			return r;

		return get_pos_less(z, y + 1, r, limit);
	}

	int get_pos_less(i64 limit) {
		return get_pos_less(0, 0, n-1, limit);
	}


	// find_first and find_last call all FALSE elements
	// to the left (right) of the sought position exactly once

	int find_first(int ll, int rr, const function<bool(const node&)> &f) {
		assert(0 <= ll && ll <= rr && rr <= n - 1);
		return find_first(0, 0, n - 1, ll, rr, f);
	}

	int find_last(int ll, int rr, const function<bool(const node&)> &f) {
		assert(0 <= ll && ll <= rr && rr <= n - 1);
		return find_last(0, 0, n - 1, ll, rr, f);
	}
};

int main() {

	int n;
	int64_t T;
	scanf("%d", &n);
	scanf("%" PRIi64, &T);

	vector<int64_t> a(n+1);
	for (int i = 0; i < n; i++)
	{
		scanf("%" PRIi64, &a[i]);
	}

	segtree tr(a);

	int pos = 0;
	i64 cnt = 0;
	auto m = T;
	auto ac = n;
	while (ac > 0 && m > 0) { //have kiosks and money
		if (pos == 0) {
			auto ts = tr.get(0, n - 1);
			if (ts.sum <= m) {
				i64 k = (m / ts.sum) * ts.count;
				cnt += k;
				m %= ts.sum;
				ac = ts.count;
			}
		}
		if (m == 0)
			break;

		i64 first_sum = 0;
		if (pos > 0)
			first_sum = tr.get(0, pos-1).sum;
		int i = tr.get_pos_less(m + first_sum);

		if (i > pos) { //buy somewhat
			auto cc = tr.get(pos, i - 1);
			if (cc.count > 0) {
				cnt += cc.count;
				m -= cc.sum;
			}
		}
		if (i < n) {
			tr.modify(i, i, -a[i]);
			ac--;
			pos = i + 1;
			if (pos == n)
				pos = 0;
		}

		if (i >= n) {
			pos = 0;
		}
	}
	printf("%" PRIi64, cnt);
	return 0;
}
