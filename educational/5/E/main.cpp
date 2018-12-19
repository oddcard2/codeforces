#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define MOD 1000000007ll

template<typename T>
T progress_sum_mod(T start, T end, T m) {
	T n = (end - start + 1) % m;
	return (((start - 1) % m)*n + n * (n + 1) / 2) % m;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll m, n;
	cin >> n >> m;

	ll ans = 0;
	ans += ((n % MOD) * (m % MOD) % MOD);

	ll sub = 0;
	
	ll nr = sqrt(n);
	ll lim = min(m, nr);
	for (ll i = 1; i <= lim; i++) {
		sub += ((n / i)*i) % MOD;
		if (sub > MOD)
			sub %= MOD;
	}

	for (ll i = 1; i <= nr; i++) {
		ll low = n / (i + 1) + 1;
		ll up = n / i;
		if (low > m)
			continue;
		if (up > m)
			up = m;

		if (low <= lim && lim <= up)
			continue;

		ll val = progress_sum_mod(low, up, MOD);
		sub += (i*val) % MOD;
		if (sub > MOD)
			sub %= MOD;
	}

	ans = (ans - sub + MOD) % MOD;
	cout << ans;

	return 0;
}