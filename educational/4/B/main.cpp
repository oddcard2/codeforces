#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n;

	cin >> n;

	vector<pair<ll, ll>> f(n);

	for (ll i = 0; i < n; i++)
	{
		ll v;
		cin >> v;
		f[i] = { v, i };
	}

	sort(begin(f), end(f), [&](pair<ll, ll> a, pair<ll, ll> b) { return a.first < b.first; });

	ll ans = 0;
	for (ll i = 1; i < n; i++)
	{
		ans += abs(f[i - 1].second - f[i].second);
	}

	cout << ans;

	return 0;
}