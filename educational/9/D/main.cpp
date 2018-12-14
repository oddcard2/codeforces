#include "bits/stdc++.h"

using namespace std;

typedef long long ll;


//Soultion from tutorial:
#if 1

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	//int n = 1000000;

	int n, m;
	cin >> n >> m;

	vector<int> aa(n);
	vector<int> a(1000000 + 1);

	vector<int> gd(n);
	int gn = 0;
	//vector<int> id(1000000 + 1);

	int num = 0;
	int mx = 0;
	for (int i = 0; i < n; i++)
	{
		int v;
		cin >> v;
		aa[i] = v;
		if (v <= m) {
			a[v]++;
			if (v > mx)
				mx = v;
		}
	}

	for (int i = 1; i <= mx; i++)
	{
		if (a[i]) {
			gd[gn++] = i;
		}
	}

	if (mx == 0) {
		cout << "1 0";
		return 0;
	}

	vector<int> z(m + 1);
	for (int i = 0; i < gn; i++)
	{
		int v = gd[i];
		for (int j = 1; j*v <=m ; j++)
		{
			z[j*v] += a[v];
		}
	}

	mx = 0;
	int ans = m;
	for (int i = m; i >=1 ; --i)
	{
		if (z[i] >= mx) {
			ans = i;
			mx = z[i];
		}
	}

	cout << ans << " " << mx << '\n';
	for (int i = 0; i < n; i++)
	{
		if (ans % aa[i] == 0) {
			cout << i+1 << " ";
		}
	}

	return 0;
}

#else
vector<int> lp;
vector<int> pr;

//lp is from ZERO!
void prime_sieve_linear(int n) {
	for (int i = 2; i <= n; ++i) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && i*pr[j] <= n; ++j)
			lp[i * pr[j]] = pr[j];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	//int n = 1000000;

	int n, m;
	cin >> n >> m;

	vector<int> aa(n);
	vector<int> a(1000000+1);
	//vector<int> id(1000000 + 1);

	int num = 0;
	int mx = 0;
	for (int i = 0; i < n; i++)
	{
		int v;
		cin >> v;
		aa[i] = v;
		if (v <= m) {
			a[v]++;
			if (v > mx)
				mx = v;
		}
	}

	if (mx == 0) {
		cout << "1 0";
		return 0;
	}

	lp.resize(1000000 + 1);
	prime_sieve_linear(1000000);

	//factorization
	//360 = 2*2*2*3*3*5
	vector<pair<int,int>> f(300);

	function<void(int)> fact = [&](int t) {
		int i = 0;
		f[1] = { 0,0 };
		while (t > 1) {
			int pp = lp[t];
			if (f[i].first == pp) {
				f[i].second++;
			}
			else {
				i++;
				f[i].first = pp;
				f[i].second = 1;
				f[i + 1].first = 0;
			}
			t /= pp;
		}
	};

	int best = 0;
	int bestm;
	int cnt = 0;
	function<void(int, int)> gen = [&](int r, int i) {
		if (f[i].first == 0) {

			cnt += a[r];
			//cout << r << '\n';
			return;
		}

		int v = r;
		for (int j = 0; j <= f[i].second; j++)
		{
			gen(v, i + 1);
			v *= f[i].first;
		}
	};


	//fact(360);
	//gen(1, 1);

	//fact(256);
	//gen(1, 1);

	//return 0;
	int cm = m;
	while (cm > 0) {

		cnt = 0;
		fact(cm);
		gen(1, 1);
		if (cnt >= best) {
			best = cnt;
			bestm = cm;
		}
		cm--;
	}

	vector<int> pos;
	for (int i = 0; i < n; i++)
	{
		if (bestm % aa[i] == 0) {
			pos.push_back(i + 1);
		}
	}

	cout << bestm << " " << pos.size() << '\n';
	if (!pos.empty()) {
		for (auto p: pos)
		{
			cout << p << " ";
		}
	}

	return 0;
}
#endif