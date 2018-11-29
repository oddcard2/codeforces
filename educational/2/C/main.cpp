#include "bits/stdc++.h"

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s;
	getline(cin, s);

	int stat[26] = { 0 };

	for (auto c : s) {
		stat[c - 'a']++;
	}

	int cnt = 0;
	for (int i = 0; i < 26; i++)
	{
		if (stat[i] % 2) {
			cnt++;
		}
	}
	if (cnt > 1) {
		//changes
		int i = 0, j = 25;
		while (j > i) {
			for (; i < 26; i++) {
				if (stat[i] % 2) {
					break;
				}
			}
			for (; j >= 0; j--) {
				if (stat[j] % 2) {
					break;
				}
			}
			if (i < 26 && j >= 0) {
				stat[i]++;
				stat[j]--;
			}
		}
	}
	//output
	int center = -1;
	for (int i = 0; i < 26; i++)
	{
		if (stat[i] % 2) {
			center = i;
			break;
		}
	}

	for (int i = 0; i < 26; i++) {
		if (!stat[i])
			continue;

		int num = stat[i] / 2;
		for (int j = 0; j < num; j++) {
			cout << (char)(i + 'a');
		}
		//stat[i] -= num;
	}
	if (center >= 0) {
		cout << (char)(center + 'a');
	}

	for (int i = 25; i >=0; i--) {
		if (!stat[i])
			continue;

		int num = stat[i] / 2;
		for (int j = 0; j < num; j++)
			cout << char(i + 'a');
	}

	return 0;
}