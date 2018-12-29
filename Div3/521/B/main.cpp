#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	int  k = 0;
	for (int i = 2; i < n; i++)
	{
		if (a[i - 2] == 1 && a[i - 1] == 0 && a[i] == 1) {
			a[i] = 0;
			k++;
		}
	}

	cout << k;

	return 0;
}