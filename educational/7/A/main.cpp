#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n;
	cin >> n;

	ll i = 0;
	ll cnt = 0;
	while (cnt < n) {
		i++;
		cnt = i * (i + 1) / 2;
	}

	i--;
	cnt = i * (i + 1) / 2;
	ll ans = n - cnt;

	cout << ans;

	return 0;
}