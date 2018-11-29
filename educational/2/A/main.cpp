#include "bits/stdc++.h"

using namespace std;

int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s;
	getline(cin, s);

	auto isuint = [&](int b, int e) {
		if (b == e) {
			return false;
		}
		if (s[b] == '0') {
			return b + 1 == e;
		}
		for (int i = b; i < e; i++) {
			if (!isdigit(s[i]))
				return false;
		}
		return true;
	};

	string s1, s2;

	int c1 = 0, c2 = 0;

	int b = 0;
	int e = 0;
	for (int i = 0; i <= s.length(); i++)
	{
		if (i == s.length() || s[i] == ';' || s[i] == ',') {
			e = i;
			bool digit = isuint(b, e);
			if (digit) {
				if (c1)
					s1.append(",");
				s1.append(s, b, e - b);
				c1++;
			}
			else {
				if (c2)
					s2.append(",");
				s2.append(s, b, e - b);
				c2++;
			}
			b = e + 1;
		}
	}
	if (!c1)
		cout << "-\n";
	else
		cout << "\"" << s1 << "\"\n";
	if (!c2)
		cout << "-\n";
	else
		cout << "\"" << s2 << "\"\n";

	return 0;
}