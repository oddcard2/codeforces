#include "bits/stdc++.h"
//http://codeforces.com/contest/1058/problem/D

using namespace std;

//string input = "36000000 85100000 1332";

string input = "4 4 7";

int main(int argc, char **argv) {
	cout.sync_with_stdio(false);
	cin.sync_with_stdio(false);

	istream *pinp;
#ifndef ONLINE_JUDGE
	unique_ptr<istream> stream;
	if (argc > 1) {
		pinp = new ifstream(argv[1]);
		stream.reset(pinp);
	}
	else if (!input.empty()) {
		pinp = new istringstream(input);
		stream.reset(pinp);
	} else
#endif	
	{
		pinp = &cin;
	}
	istream &icp = *pinp;

	int n, m, k;
	icp >> n >> m >> k;

	uint64_t s2 = (uint64_t)n*m * 2;

	if (k < 2 || (s2 % k != 0)) {
		cout << "NO";
		return 0;
	}

	int t = k;
	vector<int> f;
	for (int i = 2; i*i <= k && t > 1; i++) {
		while (t % i == 0) {
			f.push_back(i);
			t = t / i;
			if (t == 1)
				break;
		}
	}

	if (t > 1)
		f.push_back(t);

	int n2 = n, m2 = m;
	vector<int> nf;
	for (auto i = 0; i < f.size(); i++) {
		if (n2 % f[i] == 0) {
			n2 = n2 / f[i];
			continue;
		}
		if (m2 % f[i] == 0) {
			m2 = m2 / f[i];
			continue;
		}

		nf.push_back(f[i]);
	}

	if (nf.size() > 1 || (!nf.empty() && nf[0] != 2)) {
		cout << "NO";
		return 0;
	}

	if (nf.empty()) {
		if (n2 < n) {
			n2 = 2 * n2;
		}
		else if (m2 < m) {
			m2 = 2 * m2;
		}
	}
	
	cout << "YES" << endl;
	cout << "0 0" << endl;
	cout << n2 << " 0" << endl;
	cout << "0 " << m2 << endl;

	return 0;
}