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

	ll ans = 0;

	for (ll j = 1; j <= k + 2; j++)
	{
		ll mm = 1;
		ll den = 1;
		ll val = 1;
		for (ll i = 1; i <= k + 2; i++)
		{
			if (i == j)
				continue;

			//mm = (n - v[i]) / (1 - v[i]);
			den *= (j - i + MOD) % MOD;
			den %= MOD;
			val *= (n - i + MOD) % MOD;
			val %= MOD;

			//mm *= val;
			//if (mm > MOD)
			//	mm %= MOD;            
		}
		den = get_inv_prime(den, MOD);
		mm = (den * val) % MOD;

		ans += v[j] * mm;
		ans %= MOD;
	}
#if 0	
	for (ll i = 2; i <= k+1; i++)
	{
		//remove current
		ll prev_den = get_inv_prime((1 - v[i]), MOD);
		ll prev_num = (n - v[i]) % MOD;

		mm *= prev_den;
		mm %= MOD;
		
		mm *= get_inv_prime(prev_den, MOD);
		mm %= MOD;

		//add prev
		ll del = get_inv_prime((1 - v[i-1]), MOD);
		ll val = (((n - v[i-1]) % MOD) * del) % MOD;
		mm *= val;
		if (mm > MOD)
			mm %= MOD;

		ans += (v[i] * mm) % MOD;
	}
#endif
	cout << ans;

	return 0;
}