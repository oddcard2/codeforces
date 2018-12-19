#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define MOD 1000000007ll

template<typename T>
T binpow_mod(T a, int n, int p) {
	T res = 1;
	while (n) {
		if (n & 1) {
			res *= a;
			if (res >= p)
				res %= p;
		}
		a *= a;
		if (a >= p)
			a %= p;
		n >>= 1;
	}
	return res;
}

template<typename T>
T get_inv_prime(T a, T p) {
	return binpow_mod(a, p - 2, p);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, k;
	cin >> n >> k;

	vector<ll> v(k+3);

	//1+2^k+3^k+...
	//a(1) = 1
	//a(2) = 1 + 2^k
	//a(3) = 1 + 2^k + 3^k
	ll sum = 1;
	v[1] = 1;
	for (ll i = 2; i <= k+2; i++)
	{
		sum += binpow_mod(i, (int)k, (int)MOD);
		if (sum > MOD)
			sum %= MOD;
		v[i] = sum;
	}

	if (n <= k + 2) {
		cout << v[n];
		return 0;
	}

	ll ans = 0;

	ll j = 1;
	ll mm;

	//for x1
	ll den = 1;
	ll val = 1;
	for (ll i = 1; i <= k + 2; i++)
	{
		if (i == j)
			continue;

		den *= (j - i + MOD) % MOD;
		den %= MOD;
		val *= (n - i + MOD) % MOD;
		val %= MOD;  
	}
	den = get_inv_prime(den, MOD);
	mm = (den * val) % MOD;

	ans += v[j] * mm;
	ans %= MOD;

	for (j = 2; j <= k + 2; j++) {
		//denominator
		mm *= (((j - 1) - (k + 2) + MOD) % MOD);
		mm %= MOD;
		
		mm *= get_inv_prime((j - 1 + MOD) % MOD, MOD);
		mm %= MOD;

		//enumerator
		mm *= get_inv_prime((n - j), MOD);
		mm %= MOD;

		mm *= (n - (j - 1));
		mm %= MOD;

		ans += v[j] * mm;
		ans %= MOD;
	}

	cout << ans;

	return 0;
}