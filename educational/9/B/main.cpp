#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n;
	cin >> n;
	vector<ll> p(n);
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
	}
	string s;
	cin >> s;

	ll f = 0;
	int i = 0;
	for (auto c : s) {
		if (c == 'B') {
			f += p[i];
		}
		i++;
	}

	ll mx = f;
	ll ff = f;
	for (int i = 0; i < n; i++)
	{
		if (s[i] == 'A') {
			ff += p[i];
		}
		else {
			ff -= p[i];
		}
		mx = max(mx, ff);
	}

	ff = f;
	for (int i = n - 1; i >= 0; i--) {
		if (s[i] == 'A') {
			ff += p[i];
		}
		else {
			ff -= p[i];
		}
		mx = max(mx, ff);
	}

	cout << mx;

	return 0;
}