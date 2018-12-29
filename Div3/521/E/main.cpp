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

	vector<int> num;

	sort(begin(a), end(a));

	int mx = 0;
	int pos = 0;
	for (int i = 0; i <= n; i++) {
		if (i == n || a[i] != a[pos]) {
			int cnt = i - pos;
			mx = max(cnt, mx);

			num.push_back(cnt);
			pos = i;
		}
	}

	sort(begin(num), end(num));

	vector<int> dp(mx+1);
	for (int i = 0; i < num.size(); i++)
	{
		for (int j = num[i]; j > 0; j--)
		{
			dp[j] = max(dp[j], j);
			if (j%2==0) {
				dp[j] = max(dp[j], dp[j / 2] + j);
			}
		}
	}

	mx = 0;
	for (int i = 1; i < dp.size(); i++)
	{
		mx = max(dp[i], mx);
	}

	cout << mx;
	return 0;
}