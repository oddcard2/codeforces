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

	map<int, int> m;

	vector<int> b;
	b.push_back(1);
	bool open = true;
	for (int i = 0; i < n; i++)
	{
		m[a[i]]++;

		if (m[a[i]] == 2) {
			m.clear();
			b.push_back(i + 1);
			open = false;
			if (i < n - 1) {
				b.push_back(i + 2);
				open = true;
			}
		}
	}
	bool ok = true;
	if (open) {
		if (b.size() == 1) {
			ok = false;
		}
		else {
			b.erase(prev(end(b)));
			b.erase(prev(end(b)));

			m.clear();
			int start = *prev(end(b)) - 1;
			for (int i = start; i < n; ++i) {
				if (m[a[i]] > 2) {
					ok = false;
					break;
				}
			}
			if (ok) {
				b.push_back(n);
			}
		}
	}
	if (!ok) {
		cout << "-1";
		return 0;
	}

	cout << b.size() / 2 << endl;
	for (int i = 0; i < b.size(); i+=2)
	{
		cout << b[i] << " " << b[i + 1] << '\n';
	}

	return 0;
}