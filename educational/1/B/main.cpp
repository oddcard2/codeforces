#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string line;
	getline(cin, line);


	string tmp(line);

	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int l, r, k;
		cin >> l >> r >> k;
		l--; r--;

		int len = r - l + 1;
		int npos = (k%len);

		for (int j = 0; j < len; j++)
		{
			tmp[(npos + j) % len] = line[l + j];
		}
		for (int j = 0; j < len; j++) {
			line[l + j] = tmp[j];
		}
	}
	cout << line << '\n';
	return 0;
}