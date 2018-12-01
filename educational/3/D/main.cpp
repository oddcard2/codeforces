#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

template<class T>
class FenwickMinTree
{
public:
	template<class ForwardIt>
	FenwickMinTree(ForwardIt begin, ForwardIt end) {
		_size = (int)std::distance(begin, end);
		_d.assign(_size, numeric_limits<T>::max());
		_v.assign(begin, end);

		for (int i = 0; i < _size; i++) {
			apply(i, _v[i]);
		}
	}

	FenwickMinTree(const vector<T>& v) : FenwickMinTree(begin(v), end(v)) {
	}

	FenwickMinTree(int size) {
		_size = size;
		_d.assign(_size, 0);
		_v.assign(_size, 0);
	}

	T get(int pos) const { return _v[pos]; }

	void apply(int pos, T val) {
		//updates sums
		int p = pos;
		while (p < _size) {
			_d[p] = min(val, _d[p]);
			p = p | (p + 1);
		}

	}

	T query(int endPos) const {
		int p = endPos;
		T v = numeric_limits<T>::max();
		while (p >= 0) {
			v = min(_d[p], v);
			p = p & (p + 1);
			p = p - 1;
		}
		return v;
	}
private:
	std::vector<T> _v;
	std::vector<T> _d;
	int _size;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, m, k, s;
	cin >> n >> m >> k >> s;

	vector<ll> a(n);
	vector<ll> b(n);

	for (ll i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (ll i = 0; i < n; i++)
	{
		cin >> b[i];
	}

	FenwickMinTree<ll> dt(a);
	FenwickMinTree<ll> ft(b);

	vector<pair<ll,ll>> gd;
	vector<pair<ll,ll>> gf;

	for (ll i = 0; i < m; i++)
	{
		ll t, p;
		cin >> t >> p;
		if (t == 1)
			gd.push_back({ p, i + 1 });
		else
			gf.push_back({ p, i + 1 });
	}

	sort(begin(gd), end(gd), [](pair<ll, ll> a, pair<ll, ll> b) { return a.first < b.first; });
	sort(begin(gf), end(gf), [](pair<ll, ll> a, pair<ll, ll> b) { return a.first < b.first; });

	vector<pair<int, int>> ans;
	int d1, d2;

	auto ok = [&](ll d, int out) {
		ll md = dt.query(d);
		ll mf = ft.query(d);

		if (out) {
			for (int i = 0; i <= d; i++)
			{
				if (md == a[i]) {
					d1 = i + 1;
					break;
				}
			}
			for (int i = 0; i <= d; i++)
			{
				if (mf == b[i]) {
					d2 = i + 1;
					break;
				}
			}
		}

		ll sum = 0;
		int j = 0, jj = 0;
		int nn;
		for (ll i = 0; i < k; i++)
		{
			ll pr = -1;
			int type = 1;
			if (j < gd.size()) {
				pr = md * gd[j].first;
				nn = gd[j].second;
			}
			if (jj < gf.size()) {
				ll pp = mf * gf[jj].first;
				if (pr < 0 || pp < pr) {
					type = 2;
					pr = pp;
					nn = gf[jj].second;
				}
			}

			if (type == 1)
				++j;
			else
				++jj;

			if (out) {
				int dd = (type == 1) ? d1 : d2;
				ans.push_back({ nn, dd });
			}

			sum += pr;
			if (sum > s)
				return false;
		}
		return true;
	};

	ll l = -1, r = n, c;
	while (r - l > 1) {
		c = (l + r) / 2;
		if (ok(c, 0))
			r = c;
		else
			l = c;
	}

	if (r == n)
		cout << "-1";
	else {
		cout << r + 1 << '\n';
		ok(r, 1);
		for (size_t i = 0; i < ans.size(); i++)
		{
			cout << ans[i].first << " " << ans[i].second << '\n';
		}
	}


	return 0;
}