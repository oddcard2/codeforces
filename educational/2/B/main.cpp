#include "bits/stdc++.h"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<int> v1(n);

	struct node
	{
		int val;
		int num;
		int cnt;
	};
	vector<node> v2(m);

	for (int i = 0; i < n; i++)
	{
		cin >> v1[i];
	}
	for (int i = 0; i < m; i++)
	{
		cin >> v2[i].val;
		v2[i].num = i;
	}

	sort(begin(v1), end(v1));

	sort(begin(v2), end(v2), [](node& a, node& b) { return a.val < b.val; });

	int cnt = 0;
	int p2 = 0;
	for (int i = 0; i < m; i++) {
		while (p2 < n && v1[p2] <= v2[i].val) {
			cnt++;
			p2++;
		}
		v2[i].cnt = cnt;
	}

	sort(begin(v2), end(v2), [](node& a, node& b) { return a.num < b.num; });
	for (int i = 0; i < m; i++) {
		cout << v2[i].cnt << " ";
	}
	return 0;
}