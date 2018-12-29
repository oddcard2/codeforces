#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

pair<int, int> bin_search(int n, std::function<bool(int)> ok) {
	int l = -1, r = n, mid;
	while (r - l > 1) {
		mid = (l + r) / 2;
		if (!ok(mid))
			r = mid;
		else
			l = mid;
	}
	return { l,r };
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	cin >> n >> k;
	vector<int> a(n);

	int mx = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		mx = max(a[i], mx);
	}
	vector<pair<int,int>> num(mx + 1);
	for (int i = 0; i < n; i++)
	{
		num[a[i]].second = a[i];
		num[a[i]].first++;
	}

	sort(begin(num), end(num));

	//reverse(begin(num), end(num));

	auto check = [&](int c) {
		int res = 0;
		if (c == 0)
			return true;
		for (int i = num.size() - 1; i >= 0; i--) {
			int cnt = num[i].first / c;
			if (!cnt)
				break;
			res += cnt;
			if (res >= k)
				break;
		}

		return res >= k;
	};

	auto res = bin_search(n+1, check);
	mx = res.first;

	//cout << mx;
	vector<int> ans;
	for (int i = num.size()-1; i >= 0; i--)
	{
		int cnt = num[i].first / mx;
		if (!cnt)
			break;
		for (int j = 0; j < cnt; j++)
		{
			ans.push_back(num[i].second);
			if (ans.size() == k)
				break;
		}
		if (ans.size() == k)
			break;
	}

	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << ' ';
	}
	return 0;
}