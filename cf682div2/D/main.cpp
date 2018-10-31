#include "bits/stdc++.h"

using namespace std;

string input = "9 12 4\n"\
"bbaaababb\n"\
"abbbabbaaaba\n";

struct State
{
	int p1;
	int p2;
	int len = 0;
};

State dp[1001][1001];

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
	string s1, s2;
	std::getline(icp, s1); //empty

	std::getline(icp, s1);
	std::getline(icp, s2);

	cout << s1 << endl;
	cout << s2 << endl;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (s1[i] == s2[j]) {
				if (dp[i][j].p1 == i && dp[i][j].p2 == j)
					dp[i + 1][j + 1].len = dp[i][j].len + 1;
				else
					dp[i + 1][j + 1].len = 1;
				dp[i + 1][j + 1].p1 = i + 1;
				dp[i + 1][j + 1].p2 = j + 1;
			}
			else {
				if (dp[i][j + 1].len > dp[i + 1][j].len) {
					dp[i + 1][j + 1] = dp[i][j + 1];
				}
				else {
					dp[i + 1][j + 1] = dp[i+1][j];
				}
			}
		}
	}

	cout << dp[n][m].len << " " << dp[n][m].p1 << " " << dp[n][m].p2 << endl;

	return 0;
}