#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin >> t;

	vector<ll> a(t);

	for (int i = 0; i < t; i++)
	{
		cin >> a[i];
	}

	vector<ll> pows;
	pows.push_back(1);
	ll v = 1;
	while (v <= 1000000000ll) {
		v *= 2;
		pows.push_back(v);
	}

	auto less_p = [&](ll v) {
		for (size_t i = 0; i < pows.size(); ++i) {
			if (pows[i] > v) {
				return pows[i - 1];
			}
		}
	};

	for (int i = 0; i < t; i++) {
		ll v = a[i];
		ll ans = v * (v + 1) / 2 - 2*(less_p(v) * 2 - 1);
		cout << ans << '\n';
	}

	return 0;
}