#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> a(n);
	vector<int> b(n);

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	int j = 0;
	for (int i = 0; i <= n; i++)
	{
		if (i == n || a[i] != a[j]) {
			for (int k = j; k < i; ++k) {
				b[k] = i;
			}
			j = i;
		}
	}

	for (int i = 0; i < m; i++)
	{
		int l, r, x;
		cin >> l >> r >> x;
		l--; r--;

		int ans = -1;
		if (a[l] != x) {
			ans = l + 1;
		}
		else {
			if (b[l] <= r) {
				ans = b[l] + 1;
			}
		}
		cout << ans << '\n';
	}

	return 0;
}