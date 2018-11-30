#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;

	vector<int> a(n);

	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}

	int sum = accumulate(begin(a), end(a), 0);

	int mean = sum / n;
	int bigs = sum - mean * n;

	vector<int> b;
	copy_if(begin(a), end(a), back_inserter(b), [&](int v) { return v > mean; });

	int bigs_avail = count_if(begin(b), end(b), [&](int v) { return v == mean + 1; });
	int sum2 = accumulate(begin(b), end(b), 0);

	int count2 = (int)b.size();
	int keep_bigs = min(bigs, bigs_avail);
	int need_bigs = min(bigs - keep_bigs, count2 - keep_bigs);

	count2 -= keep_bigs;
	sum2 -= keep_bigs * (mean + 1);

	int need_mean = max(count2 - need_bigs, 0);

	int transitions = sum2 - need_bigs*(mean + 1) - need_mean * mean;

	cout << transitions;
	return 0;
}