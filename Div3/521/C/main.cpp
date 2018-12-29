#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	ll sum = 0;
	vector<pair<int,int>> a(n);
	for (int i = 0; i < n; i++)
	{
		cin >> a[i].first;
		sum += a[i].first;
		a[i].second = i;
	}

	sort(begin(a), end(a), [](pair<int, int> v1, pair<int, int> v2) { return v1.first < v2.first; });

	vector<int> ans;
	ll swm = sum - a[n - 1].first;
	if (a[n - 2].first == swm - a[n - 2].first) {
		//add all max elem
		auto l = lower_bound(begin(a), end(a), make_pair(a[n - 1].first, 0), [](pair<int, int> v1, pair<int, int> v2) { return v1.first < v2.first; });
		auto r = upper_bound(begin(a), end(a), make_pair(a[n - 1].first, 0), [](pair<int, int> v1, pair<int, int> v2) { return v1.first < v2.first; });
		for (auto it = l; it != r; ++it)
			ans.push_back(it->second+1);
	}
	if (swm > a[n - 1].first) {
		ll elem = swm - a[n - 1].first;
		if (elem <= a[n - 1].first) {
			auto e = lower_bound(begin(a), end(a), make_pair(a[n - 1].first, 0), [](pair<int, int> v1, pair<int, int> v2) { return v1.first < v2.first; });
			auto l = lower_bound(begin(a), e, make_pair(elem, 0), [](pair<int, int> v1, pair<int, int> v2) { return v1.first < v2.first; });
			auto r = upper_bound(begin(a), e, make_pair(elem, 0), [](pair<int, int> v1, pair<int, int> v2) { return v1.first < v2.first; });
			if (l != e && l->first == elem) {
				for (auto it = l; it != r; ++it)
				{
					ans.push_back(it->second + 1);
				}
			}
		}
	}

	cout << ans.size() << '\n';
	for (auto s: ans)
	{
		cout << s << ' ';
	}
	return 0;
}