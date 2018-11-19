#define _CRT_SECURE_NO_WARNINGS
#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define forll(i, n) for (ll i = 0; i < (n); ++i)
#define scll(x) scanf("%I64d", &(x))
#define scll2(x, y) scanf("%I64d %I64d", &(x), &(y))
#define prll(x) printf("%I64d", x)


int main() {
	ll n, T;

	scll2(n, T);
	vector<ll> a(n);
	forll(i, n) 
		scll(a[i]);

	ll ans = 0;
	while (1) {
		ll sum = 0, cnt = 0;
		forll(i, n) {
			if (a[i] <= T-sum) {
				cnt++;
				sum += a[i];
			}
		}
		if (sum == 0) {
			break;
		}

		ans += (T / sum) * cnt;
		T -= (T / sum) * sum;
	}

	prll(ans);
	return 0;
}
