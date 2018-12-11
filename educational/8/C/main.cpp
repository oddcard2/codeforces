#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	string s;

	cin >> n >> k >> s;


	string ans = s;
	for (int i = 0; i < s.size() && k > 0; i++)
	{
		int diff;
		if (s[i] - 'a' > 'z' - s[i]) {
			diff = min(s[i] - 'a', k);
			ans[i] = s[i] - diff;
		}
		else {
			diff = min('z' - s[i], k);
			ans[i] = s[i] + diff;
		}
		
		k -= diff;
	}


	if (k > 0) {
		cout << "-1";
		return 0;
	}


	cout << ans;
	return 0;
}