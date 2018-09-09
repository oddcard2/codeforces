#include "bits/stdc++.h"
//#include <string>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <memory>

using namespace std;

string input = "2 5 0\n01001\n10110";

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

	std::string line;
	std::getline(icp, line); //current line

	vector<vector<char> > days;
	days.resize(n);
	int i = 0;
	while (std::getline(icp, line)) {
		cout << line << endl;

		days[i].resize(m);
		transform(begin(line), end(line), begin(days[i]), [](const char s) { return (char)(s - '0'); });
		i++;
	}
	
	//int max_ones[500];
	struct item
	{
		int before;
		int count;
		int after;
	};
	int days_dp[500];




	memset(&days_dp, 0, sizeof(int)*k); //0-k skips

	//compress days
	int total_ones_max = 0;
	for (int i = 0; i < n; i++) {
		int max_ones = 0;
		item day_state[500];
		memset(&day_state, 0, sizeof(item)*m);

		int items = 0;
		int ones_sum = 0;
		int prev = 1;
		int prev_zeros = 0;

		int start = 0;
		for (start = 0; start < m && days[i][start] == 0; start++) {
		}
		day_state[0].before = start;
		for (int j = start; j < m; j++) {
			if (days[i][j] == 0) {
				if (prev == 1) {
					prev_zeros = 0;
					if (day_state[items].count > max_ones)
						max_ones = day_state[items].count;
				}
				prev_zeros++;
				prev = 0;
			}
			else { //1
				if (prev == 0) {
					//add new item if required
					day_state[items++].after = prev_zeros;
					day_state[items].before = prev_zeros;
					prev_zeros = 0;
				}

				day_state[items].count++;
				ones_sum++;
				prev = 1;
			}
		}
		day_state[items].after = prev_zeros;
		if (day_state[items].count > max_ones)
			max_ones = day_state[items].count;
		
		//DP
		//1. bymax ones
		if (total_ones_max < max_ones) {
			for (int j = total_ones_max + 1; j < max_ones; j++) {
				int skips = ones_sum - j;

				//skipped before
				for (int s=0;s<k-j;s++){
					if (skips <= k && days_dp)
				}
				
			}
			total_ones_max = max_ones;
		}
		//2. by items
		//seq ends on end of item
		//
		for (int j = 1; j < items; j++) {

		}

	}

	return 0;
}