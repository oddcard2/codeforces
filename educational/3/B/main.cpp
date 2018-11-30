#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;

	cin >> n >> m;

	vector<int> a(m);
	for (int i = 0; i < n; i++)
	{
		int b;
		cin >> b;

		a[b - 1]++;
	}

	ll ans = 0;
	for (int i = 0; i < m-1; i++)
	{
		for (int j = i+1; j < m; j++)
		{
			ans += a[i] * a[j];
		}
	}

	cout << ans;

	return 0;
}