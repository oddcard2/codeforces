#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string a, b;
	cin >> a >> b;

	if (a.size() != b.size()) {
		int diff = abs((int)a.size() - (int)b.size());
		string zeros(diff, '0');
		if (a.size() < b.size())
			a = zeros + a;
		else
			b = zeros + b;
	}

	int res = a.compare(b);
	if (res == 0)
		cout << "=";
	else if (res < 0)
		cout << "<";
	else
		cout << ">";

	return 0;
}