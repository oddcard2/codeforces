#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	cin >> n >> k;

	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	map<int, int> s;

	int ml = numeric_limits<int>::min();
	int l, r;
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		if (s.size() <= k) {
			for (; j < n; j++)
			{
				if (s.size() == k && s.count(a[j]) == 0)
					break;

				s[a[j]]++;
				int len = j - i + 1;
				if (len > ml) {
					ml = len;
					l = i + 1;
					r = j + 1;
				}
			}
		}
		if (j == n - 1)
			break;

		if (s[a[i]] == 1)
			s.erase(a[i]);
		else
			s[a[i]]--;
	}

	cout << l << " " << r;

	return 0;
}