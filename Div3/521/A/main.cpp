#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin >> t;

	for (int i = 0; i < t; i++)
	{
		ll a, b, k;
		cin >> a >> b >> k;

		ll rc = (k + 1) / 2;
		ll rl = k / 2;

		ll pos = a * rc - b * rl;
		cout << pos << '\n';
	}

	return 0;
}