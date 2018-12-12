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
		const string& a = aa[i];
		const string& b = aa[j];

		if (a.length() == b.length()) {
			return a.compare(b) == -1;
		}
		if (a.length() < b.length()) {
			if (b.compare(0, a.length(), a) > 0)
				return true;
			//x >= xx
			return b[a.length()] > a[a.length() - 1];
		}
		else {
			if (a.compare(0, b.length(), b) == -1)
				return true;
			//xx x
			return a[b.length()] <= b[b.length() - 1];
		}
	};

	//bool r1 = pred(4, 0);
	//bool r2 = pred(4, 1);
	//bool r3 = pred(4, 3);

	sort(begin(sn), end(sn), pred);

	stringstream ss;
	for (int i = 0; i < n; i++)
	{
		ss << aa[sn[i]];
	}

	cout << ss.str();

	return 0;
}