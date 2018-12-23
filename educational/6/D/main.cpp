#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll suma = 0, sumb = 0;
	ll n;
	cin >> n;
	vector<ll> a(n);
	for (ll i = 0; i < n; i++)
	{
		cin >> a[i];
		suma += a[i];
	}

	ll m;
	cin >> m;
	vector<ll> b(m);
	for (ll i = 0; i < m; i++)
	{
		cin >> b[i];
		sumb += b[i];
	}

	//single elem
	int k = 0;
	ll best = abs(suma - sumb);
	int na1, nb1, na2, nb2;

	for (size_t i = 0; i < a.size(); i++)
	{
		for (size_t j = 0; j < b.size(); j++)
		{
			ll v = abs((suma - a[i] + b[j]) - (sumb - b[j] + a[i]));
			if (v < best) {
				na1 = i;
				nb1 = j;
				best = v;
				k = 1;
			}
		}
	}

	if (a.size() > 1 && b.size() > 1) {

		map<ll, pair<int, int>> ma;
		for (size_t i = 0; i < a.size(); i++)
		{
			for (size_t j = i+1; j < a.size(); j++)
			{
				ma[a[i] + a[j]] = { i,j };
			}
		}

		map<ll, pair<int, int>> mb;
		for (size_t i = 0; i < b.size(); i++)
		{
			for (size_t j = i+1; j < b.size(); j++)
			{
				mb[b[i] + b[j]] = { i,j };
			}
		}

		for (auto& v: ma)
		{
			ll s = suma - v.first;
			ll req = (sumb + v.first - s) / 2;

			auto lb = mb.lower_bound(req);
			if (lb != mb.end()) {
				ll val = abs((suma - v.first + lb->first) - (sumb - lb->first + v.first));
				if (val < best) {
					na1 = v.second.first;
					na2 = v.second.second;
					nb1 = lb->second.first;
					nb2 = lb->second.second;
					best = val;
					k = 2;
				}
			}
			if (lb != mb.begin()) {
				auto lbb = --lb;
				ll val = abs((suma - v.first + lbb->first) - (sumb - lbb->first + v.first));
				if (val < best) {
					na1 = v.second.first;
					na2 = v.second.second;
					nb1 = lbb->second.first;
					nb2 = lbb->second.second;
					best = val;
					k = 2;
				}
			}
		}
	}

	cout << best << '\n';
	if (k == 0) {
		cout << "0\n";
	}
	else if (k == 1) {
		cout << "1\n";
		cout << na1 + 1 << " " << nb1 + 1;
	}
	else {
		cout << "2\n";
		cout << na1 + 1 << " " << nb1 + 1 << '\n';
		cout << na2 + 1 << " " << nb2 + 1 << '\n';
	}

	return 0;
}