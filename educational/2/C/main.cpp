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

	deque<int> q;
	for (int i = 0; i < 26; i++)
		if (stat[i] % 2)
			q.push_back(i);

	while (q.size() >= 2) {
		stat[q.front()]++;
		stat[q.back()]--;
		q.pop_back();
		q.pop_front();
	}

	string out(s);
	int n = s.size();
	int p = 0;
	for (int i = 0; i < 26; i++) {
		while (stat[i] > 1) {
			out[p] = out[n-p-1] = (char)(i + 'a');
			p++;
			stat[i] -= 2;
		}
	}
	for (int i = 0; i < 26; i++) {
		if (stat[i]) {
			out[n/2]= (char)(i + 'a');
		}
	}
	cout << out;

	return 0;
}