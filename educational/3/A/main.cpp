#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	int m;

	cin >> n;

	vector<int> a(n);

	cin >> m;

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	sort(begin(a), end(a));
	int c = 0;
	int cnt = 0;
	for (auto it = rbegin(a); it != rend(a); ++it) {
		c += *it;
		cnt++;
		if (c >= m) {
			break;
		}
	}

	cout << cnt;
	return 0;
}