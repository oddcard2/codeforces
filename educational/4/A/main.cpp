#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, p, q;
	string s;
	cin >> n >> p >> q >> s;

	int p1 = 0, p2 = 0;
	for (int i = 0; i <= n/p; i++)
	{
		int r = n - i * p;
		if (r % q == 0) {
			p1 = i;
			p2 = r / q;
		}
	}
	if (p1 || p2) {
		int offset = 0;
		cout << (p1 + p2) << '\n';
		for (int i = 0; i < p1; i++)
		{
			cout << s.substr(offset, p) << '\n';
			offset += p;
		}
		for (int i = 0; i < p2; i++)
		{
			cout << s.substr(offset, q) << '\n';
			offset += q;
		}
	}
	else {
		cout << "-1";
	}
	return 0;
}