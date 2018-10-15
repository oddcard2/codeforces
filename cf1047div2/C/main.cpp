#include "bits/stdc++.h"

using namespace std;

string input = "4\n6 9 15 30";

//string input = "5\n6 8 8 8 8";

//string input = "7\n10 10 10 7 7 7 14";

template<typename T>
static T gcd(T a, T b) {
	while (b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

template<typename T>
static T gcd_vec(const vector<T>& v) {
	assert(v.size() >= 2);

	T g = gcd<T>(v[0], v[1]);
	if (g == 1)
		return 1;

	for (auto i = 2; i < v.size(); ++i) {
		g = gcd<T>(g, v[i]);
		if (g == 1)
			break;
	}
	return g;
}

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

	int n; //<=3e5
	icp >> n;

	vector<int> a(n); //a[i] <= 1.5e7
	int m = 0;
	unordered_map<int, int> num;
	for (int i = 0; i < n; i++)
	{
		int t;
		icp >> t;
		a[i] = t;

		
	}

	if (m == 1) {
		cout << "-1";
		return 0;
	}

	int g = gcd_vec(a);
	for (int i = 0; i < n; i++) {
		a[i] /= g;
		int t = a[i];
		num[t]++;
		if (t > m)
			m = t;
	}

	vector<char> prime(m + 1, 1);
	for (size_t i = 0; i < a.size(); i++)
	{
		prime[a[i]] |= 2;
	}

	vector<pair<int, int> > num_vec;
	int k = 0;
	int min_val = m + 1;
	int min_count = n+1;
	for (auto it = num.begin(); it != num.end(); ++it) {
		num_vec.push_back(*it);
		if (it->first < min_val) {
			min_count = it->second;
			min_val = it->first;
		}
	}
	sort(begin(num_vec), end(num_vec), [](const pair<int, int>& a, const pair<int, int>& b) { return a.first < b.first;  });

	vector<pair<int, int> > mm; //prime, number

	//factorization of a[i]
	prime[0] = prime[1] = 0;
	for (int i = 2; i <= m; ++i)
		if (prime[i] & 1) {
			if (prime[i] & 2) {
				mm.push_back(make_pair(i, i));
				prime[i] = 2;
			}
			else
				prime[i] = 0;
			//if (i * 1ll * i <= m)
				for (int j = i * 2; j <= m; j += i) {
					if (prime[j] & 2) {
						mm.push_back(make_pair(i, j));
						prime[j] = 2;
					} else
						prime[j] = 0;
				}
		}

	sort(begin(mm), end(mm), [](const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second;  });

	unordered_map<int, int> pstat;
	int s = 0;
	for (auto i = 0; i < mm.size(); i++) {
		if (mm[i].second != num_vec[s].first)
			s++;
		pstat[mm[i].first] += num_vec[s].second;
	}

	vector<pair<int, int> > stat(pstat.size());
	k = 0;
	for (auto it = begin(pstat); it != end(pstat); ++it) {
		stat[k++] = *it;
	}

	sort(begin(stat), end(stat), [](const pair<int, int>& a, const pair<int, int>& b) { return a.second < b.second;  });

	for (auto it = stat.rbegin(); it != stat.rend(); ++it) {
		if (it->second < n) {
			cout << (int)(n - it->second);
			return 0;
		}
	}

	if (num.size() > 1) {
		cout << min_count;
		return 0;
	}

	cout << "-1";
	return 0;
}