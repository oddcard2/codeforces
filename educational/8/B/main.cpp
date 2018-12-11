#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s;
	cin >> s;

	ll sum = 0;
	if ((s[0] - '0') % 4 == 0)
		sum++;
	for (int i = 1; i < s.size(); i++)
	{
		if (((s[i] - '0') + (s[i - 1] - '0')*10) % 4 == 0) {
			sum += i;
		}

		if ((s[i] - '0') % 4 == 0)
			sum++;
	}

	cout << sum;

	return 0;
}