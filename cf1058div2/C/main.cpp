#include "bits/stdc++.h"
//http://codeforces.com/contest/1058/problem/C

using namespace std;


string input = "5\n01236";

//string input = "5\n73452";

//string input = "4\n1248";

static char dp[101][101][1000] = { 0 };
static int dps[101][101] = { 0 };

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

	//state - if possible to split segment [a,b) to sums S
	//[a][b][S] = 0|1
	//by default [a][a+1][a]=1
	
	int n;
	icp >> n;

	vector<int> seq(n);

	string line;
	getline(icp, line);

	getline(icp, line);

	transform(begin(line), end(line), begin(seq), [](const char c) { return c - '0';  });

	int sum = accumulate(begin(seq), end(seq), 0);

	for (int i = 0; i < n; i++) {
		dp[i][i+1][seq[i]] = 1;
		dps[i][i+1] = seq[i];
	}
	for (int l = 2; l <= n; l++) { //len of segment
		for (int s = 0; s <= n - l; s++) { //start of segment
			int e = s + l; //end of segment
			dps[s][e] = dps[s][s+1] + dps[s+1][e]; //recalc len
			dp[s][e][dps[s][e]] = 1;
			for (int k = 1; k < l; k++) { //separator
				int sum1 = dps[s][s + k];
				if (dp[s + k][e][sum1])
					dp[s][e][sum1] = 1;
				int sum2 = dps[s+k][e];
				if (dp[s][s+k][sum2])
					dp[s][e][sum2] = 1;
			}
		}
	}
	
	bool possible = false;
	if (sum == 0) {
		possible = dp[0][n][0];
	}
	else {
		for (int s = 0; s < sum; s++) { //sum
			if (dp[0][n][s]) {
				possible = true;
				break;
			}
		}
	}

	cout << (possible ? "YES" : "NO");

	return 0;
}