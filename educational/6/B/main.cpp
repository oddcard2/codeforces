#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	vector<int> sg = { 6,2,5,5,4,5,6,3,7,6 };

	int a, b;
	cin >> a >> b;

	int ans = 0;
	for (int i = a; i <=b; i++)
	{
		int v = i;
		do {
			int d = v % 10;
			v /= 10;
			ans += sg[d];
		} while (v);
	}

	cout << ans;

	return 0;
}