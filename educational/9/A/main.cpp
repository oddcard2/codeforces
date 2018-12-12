#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, p;
	cin >> n >> p;

	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		string s;
		cin >> s;
		if (s == "halfplus")
			a[i] = 1;
	}

	ll pr = p/2;
	ll cnt = 1;
	for (int i = n - 2; i >= 0; --i) {
		if (a[i] == 1) {
			cnt += cnt + 1;
			pr += cnt * p /2;
		}
		else {
			cnt = cnt * 2;
			pr += cnt * p /2;
		}
	}

	cout << pr;

	return 0;
}