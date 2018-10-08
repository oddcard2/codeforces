#include "bits/stdc++.h"

using namespace std;

string input1 = "4\n"\
"89\n"\
"88\n"\
"1000\n"\
"28923845\n";

string input2 = "1\n"\
"9432237011\n";

string input = "1\n"\
"380211\n"; //380083

string input_ = "1\n"\
"6689293529632214217419458798543\n";

string input4 = "1\n"\
"13719458802312\n";

//#define 

//1371945 8 8 02312 
// 59743
//done    -668929352963221421741945 8 8 02312
//correct -668929352963221421741945 8 7 98543
//answer - 668929352963221421741945 8 8 5 9743
//8 6 xxxx, 9743
//8 6 8541

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

	int t;
	icp >> t;

	string line;
	getline(icp, line);
	vector<char> s(2 * 100000);
	vector<int> stat(10);
	set<int> sm;
	vector<int> req_num(10);
	for (int i = 0; i < t; i++)
	{
		line.clear();
		getline(icp, line);
		s.resize(line.size());
		fill(begin(stat), end(stat), 0);
		transform(begin(line), end(line), begin(s), [](char c) { return c - '0'; });
		for_each(begin(s), end(s), [&](char c) {stat[c]++; });
		transform(begin(stat), end(stat), begin(stat), [&](int v) { return v % 2; });

		int req_num = accumulate(begin(stat), end(stat), 0);
		if (!req_num) {
			//substract 1
			for (auto i = s.size() - 1; i >= 0; i--) {
				if (s[i]) {
					s[i] = s[i] - 1;
					break;
				}
				else
					s[i] = 9;
			}
			
			//recalc stat
			for_each(begin(s), end(s), [&](char c) {stat[c]++; });
			transform(begin(stat), end(stat), begin(stat), [&](int v) { return v % 2; });
			//cout << line << endl;
			//continue;
		}

		sm.clear();
		for (auto i = 0; i < stat.size(); i++)
		{
			if (stat[i])
				sm.insert(i);
		}
		auto is_le = [&](size_t pos, size_t len) {
			size_t n = len - pos; //tail len
			if (sm.size() > n)
				return false;
			if (sm.size() < n)
				return s[pos] != 0;
			
			//sizes are eq
			for (auto r : sm) {
				if (s[pos] > r)
					return true;
				if (s[pos] < r)
					return false;
				pos++;
			}
			return true; //eq
		};
		size_t pos = 0;
		for (auto i = s.size()-1; i >=0; i--)
		{
			if (sm.find(s[i]) != end(sm))
				sm.erase(s[i]);
			else
				sm.insert(s[i]);

			if (is_le(i, s.size())) {
				pos = i;
				break;
			}
		}
		if (s.size() - pos != sm.size()) {
			int new_n = (int)(s[pos] - 1);

			if (sm.find(new_n) != end(sm))
				sm.erase(new_n);
			else
				sm.insert(new_n);
			s[pos] = new_n;
			for (auto i = pos + 1; i < s.size(); i++) {
				s[i] = 9;
			}

			if (s[0] == 0) {
				for (auto i = 0; i < s.size() - 2; i++)
					cout << (int)9;
				cout << endl;
				continue;
			}

			//greedy
			size_t start_pos = s.size() - sm.size();
			for (auto it = sm.rbegin(); it != sm.rend(); ++it) {
				s[start_pos++] = *it;
			}
		}
		else {
			auto it = sm.lower_bound(s[pos]);
			while (it == end(sm) || *it >= s[pos]) {
				--it;
			}

			s[pos] = *it;
			sm.erase(*it);

			auto start_pos = pos + 1;
			for (auto it = sm.rbegin(); it != sm.rend(); ++it) {
				s[start_pos++] = *it;
			}
		}
		
		for (auto i = 0; i < s.size(); i++) {
			cout << (int)s[i];
		}
		cout << endl;
		
	}
	return 0;
}