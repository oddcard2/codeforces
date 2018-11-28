#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define forll(i, n) for (ll i = 0; i < (n); ++i)

#define MAX_VAL 1000000000ll

ll dp[31][31][51];

#define LAZY

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);

#ifdef LOCAL
	freopen(FILE_NAME ".in", "r", stdin);
	//	freopen(FILE_NAME ".out", "w", stdout);
#endif

	ll t;
	cin >> t;
	vector<tuple<ll, ll, ll> > qs(t);

	ll mm = 0, mn = 0, mk = 0;
	forll(i, t) {
		ll n, m, k;
		cin >> n >> m >> k;
		mn = max(mn, n);
		mm = max(mm, m);
		mk = max(mk, k);
		qs[i] = { n,m,k };
	}

	for (ll n = 1; n <= mn; n++) {
		for (ll m = 1; m <= mm; m++) {
			dp[n][m][0] = 0;
			for (ll k = 1; k <= mk; k++) {
				dp[n][m][k] = MAX_VAL;
			}
		}
	}

#ifdef LAZY
	function<ll(int, int, int)> calc = [&](int n, int m, int k) -> ll {
		if (dp[n][m][k] < MAX_VAL)
			return dp[n][m][k];
		if (n*m < k || !k)
			return MAX_VAL;
		if (n*m == k) {
			dp[n][m][k] = 0;
			return 0;
		}

		//splitting by n
		for (ll i = 1; i <= n - 1; i++) {
			for (ll f = 0; f <= k; f++) { //first part
				dp[n][m][k] = min(dp[n][m][k], calc(i, m, f) + calc(n - i,m,k - f) + m * m);
			}
		}

		//splitting by m
		for (ll i = 1; i <= m - 1; i++) {
			for (ll f = 0; f <= k; f++) { //first part					 
				dp[n][m][k] = min(dp[n][m][k], calc(n,i,f) + calc(n,m - i,k - f) + n * n);
			}
		}

		return dp[n][m][k];
	};

	ll n, m, k;
	for (auto q : qs) {
		tie(n, m, k) = q;
		cout << calc(n,m,k) << '\n';
	}

	

#else
	for (ll n = 1; n <= mn; n++) {
		for (ll m = 1; m <= mm; m++) {		
			//wo splitting
			if (n*m <= mk)
				dp[n][m][n*m] = 0;
	
			for (ll i = 1; i <= n - 1; i++) {
				for (ll k = 1; k <= mk; k++) {
					for (ll f = 0; f <= k; f++) { //first part
						//splitting by n
						if (dp[i][m][f] < MAX_VAL && dp[n - i][m][k - f] < MAX_VAL)
							dp[n][m][k] = min(dp[n][m][k], dp[i][m][f] + dp[n - i][m][k - f] + m * m);
					}
				}
			}

			for (ll i = 1; i <= m - 1; i++) {
				for (ll k = 1; k <= mk; k++) {
					for (ll f = 0; f <= k; f++) { //first part
						//splitting by m
						if (dp[n][i][f] < MAX_VAL && dp[n][m - i][k - f] < MAX_VAL)
							dp[n][m][k] = min(dp[n][m][k], dp[n][i][f] + dp[n][m - i][k - f] + n * n);
					}
				}
			}
		}
	}

	ll n, m, k;
	for (auto q : qs) {
		tie(n, m, k) = q;
		cout << dp[n][m][k] << '\n';
	}
#endif
	return 0;
}