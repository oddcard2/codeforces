#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, b, p;
	cin >> n >> b >> p;

	ll sumb = 0, sump = n*p;
	while (n > 1) {
		ll k = 1;
		while (k < n) {
			k <<= 1;
		}
		if (k > n)
			k >>= 1;

		sumb += k * b + k / 2;
		n = k/2 + (n - k);
	}

	cout << sumb << " " << sump;
	return 0;
}