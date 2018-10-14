#include "bits/stdc++.h"

using namespace std;

string input = "9\n"\
"88 22 83 14 95 91 98 53 11\n"\
"3 24\n"\
"7 -8\n"\
"1 67\n"\
"1 64\n"\
"9 65\n"\
"5 12\n"\
"6 -80\n"\
"3 8\n";

int64_t a[100001];
char ec[100001] = { 0 }; //edges count
pair<int, int64_t> g[100001][3];


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
	for (int i = 0; i < n; i++)
	{
		icp >> a[i + 1];
	}

	for (int i = 0; i < n - 1; i++) {
		int x;
		int64_t c;
		icp >> x >> c;
		auto e = make_pair(x, c);
		g[i + 2][ec[i + 2]++] = make_pair(x, c);
		g[x][ec[x]++] = make_pair(i + 2, c);
	}

	//dfs
	int path_counter = 0;

	//TODO: try to use simple DP to store current max path (start and sum) from current vertex

	vector<char> used(n + 1);

	function<void(int)> dfs = [&](int v) {
		used[v] = true;
		cout << v << " ";
		for (int i = 0; i < ec[v]; ++i) {
			auto ch = g[v][i];
			int ch_v = ch.first;
			
			if (!used[ch_v]) {
				int64_t val = ch.second;
				//updates cost path
				path_counter++;
				//finds max in cost path
				bool sad_v = false;
				if (sad_v) {
					used[ch_v] = true;
					break;
				}
				dfs(ch_v);
			}
		}
		//remove v from cost path

		path_counter--;
	};

	dfs(1);
	return 0;
}