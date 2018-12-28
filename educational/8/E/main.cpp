#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define t2d(t,n,m,name) vector<vector<t>> name(n, vector<t>(m));
#define t2di(n,m,name) vector<vector<int>> name(n, vector<int>(m));
#define t2dll(n,m,name) vector<vector<ll>> name(n, vector<ll>(m));

//http://e-maxx.ru/algo/fenwick_tree
//with modifications
/***********************/
struct fenwick_tree
{
	vector<int> t;
	int n;

	fenwick_tree(int nn)
	{
		n = nn;
		t.assign(n, 0);
	}

	fenwick_tree(const vector<int>& a) : fenwick_tree((int)a.size())
	{
		for (unsigned i = 0; i < a.size(); i++)
			inc(i, a[i]);
	}

	int sum(int r)
	{
		int result = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			result += t[r];
		return result;
	}

	void inc(int i, int delta)
	{
		for (; i < n; i = (i | (i + 1)))
			t[i] += delta;
	}

	int sum(int l, int r)
	{
		return sum(r) - sum(l - 1);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	t2di(n, m, a);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			char c;
			cin >> c;
			if (c == 'z')
				a[i][j] = 1;
		}
	}

	t2di(n, m, dr);
	t2di(n, m, dl);
	t2di(n, m, dld);


	for (int i = 0; i < n; i++) {
		//to right
		int cnt = 0;
		for (int j = m - 1; j >= 0; j--)
		{
			if (a[i][j])
				cnt++;
			else
				cnt = 0;
			dr[i][j] = cnt;
		}

		//to left
		cnt = 0;
		for (int j = 0; j < m; j++)
		{
			if (a[i][j])
				cnt++;
			else
				cnt = 0;
			dl[i][j] = cnt;
		}
	}

	//to left-down
	for (int i = 0; i <= (n - 1) + (m - 1); i++) {
		int l = min(n - 1, i);
		int cnt = 0;
		for (int j = l; j >= 0; j--) {
			int col = i - j;
			if (col >= m)
				break;

			if (a[j][col])
				cnt++;
			else
				cnt = 0;

			dld[j][col] = cnt;
		}
	}

	vector<fenwick_tree> ft(n + m, fenwick_tree(max(n, m)));

	ll ans = 0;
	struct pt {
		int l;
		int c;
	};
	vector<vector<pt>> ev(m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (dr[i][j])
				ev[j + dr[i][j] - 1].push_back({ i, j });
		}
	}

	//column
	for (int i = m - 1; i >= 0; i--)
	{
		for (auto e : ev[i])
		{
			ft[e.l + e.c].inc(e.l, +1);
		}

		//line
		for (int j = 0; j < n; j++)
		{
			int c = min(dl[j][i], dld[j][i]);
			ans += ft[i + j].sum(j, j + c - 1);
		}
	}

	cout << ans;
	return 0;
}
