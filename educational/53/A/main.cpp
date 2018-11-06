#include "bits/stdc++.h"

using namespace std;

string input = "10\n"\
"codeforces";

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

	int n;
	icp >> n;
	if (n == 1) {
		cout << "NO";
		return 0;
	}
	string str;
	getline(icp, str);
	getline(icp, str);

	char prev = '\0';
	for (auto c : str) {
		if (prev != '\0' && c != prev) {
			cout << "YES" << endl;
			cout << prev << c;
			return 0;
		}
		prev = c;
	}
	cout << "NO";
	
	return 0;
}