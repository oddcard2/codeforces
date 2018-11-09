#define _CRT_SECURE_NO_WARNINGS
#include "bits/stdc++.h"

using namespace std;

string input = "";

template <typename T, typename U>
std::pair<T, U> operator-(const std::pair<T, U> & l, const std::pair<T, U> & r) {
	return { l.first - r.first, l.second - r.second };
}

template<typename T>
class FenwickTree
{
public:
	vector<T> t;
	vector<T> t2;
	int n;

	void init(int nn)
	{
		n = nn;
		t.assign(n, T());
		t2.assign(n, T());
	}

	pair<T,T> sum(int r)
	{
		T result = 0;
		T not_zero_cnt = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) {
			result += t[r];
			not_zero_cnt += t2[r];
		}
		return make_pair(result, not_zero_cnt);
	}

	void inc(int i, T delta)
	{
		for (; i < n; i = (i | (i + 1))) {
			t[i] += delta;
			t2[i] += (delta > 0) ? 1 : -1;
		}
	}

	pair<T, T> sum(int l, int r)
	{
		return sum(r) - sum(l - 1);
	}

	void init(vector<T> a)
	{
		init((int)a.size());
		for (auto i = 0; i < a.size(); i++)
			inc(i, a[i]);
	}
};

template<typename C, typename T>
int fenwick_upperbound(C t, int first, int last, T val)
{
	int f = first;
	int count = last - first;
	while (count>0)
	{
		int it = f; 
		int step = count / 2; 
		it = f + step;
		if (!(val < t.sum(first, it).first))
		{
			f = ++it; count -= step + 1;
		}
		else count = step;
	}
	return f;
}

int main() {

	int n;
	int64_t T;
	scanf("%d", &n);
	scanf("%" PRIi64, &T);

	vector<int64_t> a(n);
	//vector<int64_t> a2(n, 1);
	for (int i = 0; i < n; i++)
	{
		scanf("%" PRIi64, &a[i]);
	}

	//n = 7;
	//vector<int64_t> a = { 1,2,0,3,2,0,1 }; //1,3,3,6,8,8,9
	//vector<int64_t> a2 = { 1,1,0,1,1,0,1 };

	//FenwickTree<int64_t> c;
	//c.init(a2);
	FenwickTree<int64_t> s;
	s.init(a);

	//int p = fenwick_upperbound(s, 2, 7, 4);
	//p = fenwick_upperbound(s, 0, 7, 7);
	//p = c.sum(1, 3);

	int pos = 0;
	int cnt = 0;
	auto m = T;
	auto ac = n;
	while (ac > 0 && m > 0) { //have kiosks and money
		if (pos == 0) {
			auto ts = s.sum(n-1);
			if (ts.first >= m) {
				//auto tc = c.sum(n-1);
				int k = (m / ts.first) * ts.second;
				cnt += k;
				m %= ts.first;
				ac = ts.second;
			}
		}
		if (m == 0)
			break;

		int i = fenwick_upperbound(s, pos, n, m);
			
		auto cc = s.sum(pos, i-1);
		if (cc.second > 0) {
			cnt += cc.second;
			m -= cc.first; // s.sum(pos, i - 1);
		}
		if (i == n) {
			pos = 0;
		}
		else {
			if (pos == i) { //can't to buy
				s.inc(i, -a[i]);
				//c.inc(i, -1);
				ac--;
			}
			pos = i;
		}

	}
	printf("%d", cnt);
	return 0;
}