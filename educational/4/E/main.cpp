#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n; cin >> n;
	vector<int> p(n+1);
	map<int, int> mp;
	for (int i = 1; i <= n; i++)
	{
		cin >> p[i];
		mp[i] = p[i];
	}

	vector<bool> used(n+1);
	vector<vector<int>> cycles;
	int c = 0;
	bool ok = true;
	for (int i = 1; i <= n; i++)
	{
		if (used[i]) {
			continue;
		}

		cycles.push_back({i});
		used[i] = 1;
		int v = i;
		while (true) {
			v = mp[v];
			used[v] = 1;
			if (cycles[c][0] == v) {
				if (cycles[c].size() % 2 == 0) {
					ok = false;
				}
				break;
			}
			cycles[c].push_back(v);
			

		}
		if (!ok)
			break;
		c++;
	}

	if (!ok) {
		cout << "-1";
		return 0;
	}


	int c2 = 0;
	vector<int> ans;
	for (const auto& cc : cycles) {
		if (cycles.size() == 2) {
			continue;
			c2++;
		}
		int k = cc[0];
		int nn = cc.size();
		ans.push_back(k);
		//cout << k << " ";
		for (int i = 1; i < cc.size(); ++i) {
			k = (((k-1) - nn / 2 + nn) % nn + 1);
			ans.push_back(k);
			//cout << k << " ";
		}
	}
	//ans.push_back(ans[0]);

	if (c2 % 2 != 0) {
		cout << "-1";
		return 0;
	}

	vector<int> pr(ans.size());
	for (int i = 0; i < ans.size(); i++) {
		pr[ans[i]] = ans[i + 1];
	}

	for (int i = 1; i < pr.size(); i++) {
		cout << pr[i] << " ";
	}

	return 0;
}