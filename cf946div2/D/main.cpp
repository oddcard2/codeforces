#include "bits/stdc++.h"


using namespace std;

//string input = "2 5 0\n01001\n10110";

string input = "2 5 1\n01001\n10110";

//#define ONLINE_JUDGE

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
	}
	else
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
	vector<int> hours(n);
	days.resize(n);

	for (int i = 0; i < n; i++) {
		std::getline(icp, line);
		//cout << line << endl;

		days[i].resize(m);
		transform(begin(line), end(line), begin(days[i]), [](const char s) { return (char)(s - '0'); });
		hours[i] = std::accumulate(begin(days[i]), end(days[i]), 0);
	}

	vector<int> cost(m);

	auto calc_costs = [&](int d) {
		cost.resize(hours[d] + 1);
		fill(begin(cost), end(cost), 1000);
		cost[0] = 0;
		for (int i = 0; i < m; i++) {
			int ones = 0;
			int len = 0;

			for (int j = i; j < m; j++) {
				len++;
				ones += days[d][j];
				cost[ones] = min(cost[ones], len);
			}
		}
		return hours[d];
	};

	int total_hours = std::accumulate(begin(hours), end(hours), 0);
	vector<int> dp(total_hours + 1, 100000000);
	dp[0] = 0;

	int h_sum = 0;
	for (int i = 0; i < n; i++) //days
	{
		int max_hours = calc_costs(i);
		if (!max_hours)
			continue;

		int e = h_sum + max_hours;
		int s = max(1, h_sum + max_hours - k - 1);
		for (int k = e; k >= s; --k)
		{
			int min_add = min(max_hours, k);
			for (int j = min_add; j > 0 && k - j >= 0 && k - j <= h_sum; --j)
			{
				dp[k] = min(dp[k], dp[k - j] + cost[j]);
			}
		}
		h_sum += max_hours;
	}

	int ans = 10000000;
	//for (int i = total_hours; i >= total_hours - k; --i) {
	//	ans = min(ans, dp[i]);
	//}

	if (k >= h_sum)
		ans = 0;
	else
		for_each(end(dp) - k - 1, end(dp), [&](int v) { ans = min(ans, v); });
	cout << ans;
	return 0;
}