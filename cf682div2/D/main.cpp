#include "bits/stdc++.h"

using namespace std;

string input = "9 12 4\n"\
"bbaaababb\n"\
"abbbabbaaaba\n";

//string input = "4 4 2\n"\
//"aabd\n"\
//"aacd\n";

struct State
{
	int p1;
	int p2;
	//int maxp1;
	//int maxp2;
	int len = 0;
};

State dp[1001][1001][11];

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

	int n, m, kk;
	icp >> n >> m >> kk;
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
				//updates len
				if (dp[i][j][0].p1 == i && dp[i][j][0].p2 == j)
					dp[i + 1][j + 1][0].len = dp[i][j][0].len + 1;
				else
					dp[i + 1][j + 1][0].len = 1;

				dp[i + 1][j + 1][0].p1 = i + 1;
				dp[i + 1][j + 1][0].p2 = j + 1;

				//updates splitting

				int len = dp[i + 1][j + 1][0].len;

				//only this part
				dp[i + 1][j + 1][1].len = len;
				dp[i + 1][j + 1][1].p1 = i + 1;
				dp[i + 1][j + 1][1].p2 = j + 1;

				for (int l = 1; l <= len; l++)
				{
					if ((i + 1 - l < 0) || (j + 1 - l < 0))
						break;

					//num of parts
					for (int k = 2; k <= kk; k++) {
						if (k > 0 && dp[i + 1 - l][j + 1 - l][k - 1].len == 0) //no slitting before for k-1 parts
							break;

						//take l last symbols as last part
						dp[i + 1][j + 1][k].len = dp[i + 1 - l][j + 1 - l][k - 1].len + l;
						dp[i + 1][j + 1][k].p1 = i + 1;
						dp[i + 1][j + 1][k].p2 = j + 1;
					}
				}
			}
			//updates values
			for (int k = 1; k <= kk; k++) {
				if (dp[i][j + 1][k].len > dp[i + 1][j + 1][k].len) {
					dp[i + 1][j + 1][k] = dp[i][j + 1][k];
				}
				if (dp[i+1][j][k].len > dp[i + 1][j + 1][k].len) {
					dp[i + 1][j + 1][k] = dp[i+1][j][k];
				}
			}
		}
	}

	cout << dp[n][m][kk].len << " " << dp[n][m][kk].p1 << " " << dp[n][m][kk].p2 << endl;

	return 0;
}