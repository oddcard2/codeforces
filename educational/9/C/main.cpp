#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	vector<string> aa(n);
	vector<int> sn(n);
	for (int i = 0; i < n; i++)
	{
		cin >> aa[i];
		sn[i] = i;
	}

	auto pred = [&](int i, int j) {
		//aa[i]+aa[j] < aa[j]+aa[i]
		const string& a = aa[i];
		const string& b = aa[j];

		int len = a.length() + b.length();
		for (int i = 0; i < len; i++)
		{
			char c1 = (i < a.length()) ? a[i] : b[i - a.length()];
			char c2 = (i < b.length()) ? b[i] : a[i - b.length()];
			if (c1 < c2)
				return true;
			if (c2 < c1)
				return false;
		}
		return false;
	};

	sort(begin(sn), end(sn), pred);

	stringstream ss;
	for (int i = 0; i < n; i++)
	{
		ss << aa[sn[i]];
	}

	cout << ss.str();

	return 0;
}