#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

typedef vector<int> vi;

#define rn\
int n; cin>>n;

#define rvi(name, count)\
vi name(count);\
for (int i = 0; i < count; i++) cin >> name[i];

#define rvn \
int n; cin >> n;\
vi v(n); \
for (int i = 0; i < n; i++) cin >> v[i];

#define rvn1 \
int n; cin >> n;\
vi v(n+1); \
for (int i = 0; i < n; i++) cin >> v[i+1];

struct cycle {
	vi a;
};

vector<cycle> perm_cycles(const vi& a) {
	vector<cycle> res;
	vector<bool> used(a.size()+1); //elems starts with 1!

	for (int i = 1; i < (int)a.size()+1; i++) {
		if (used[i])
			continue;

		int start = i, curr = start;
		res.emplace_back(cycle{});
		
		do {
			res.back().a.push_back(curr);
			used[curr] = true;
			curr = a[curr - 1];
		} while (curr != start);
	}
	return res;
}

vi cycles2perm(const vector<cycle>& c, int len) {
	vi res(len + 1);
	for (auto e : c) {
		for (size_t i = 0; i < e.a.size()-1; i++)
		{
			res[e.a[i]] = e.a[i + 1];
		}
		res[e.a.back()] = e.a.front();
	}
	return res;
}

int main() {
	rvn;

	vector<cycle> vc = perm_cycles(v);
	sort(begin(vc), end(vc), [](const cycle& c1, const cycle& c2) { return c1.a.size() < c2.a.size(); });
	vector<cycle> res;
	int ok = 1;
	int pos = 0;
	while (pos < vc.size())
	{
		if (vc[pos].a.size() % 2 == 0) {
			if (pos + 1 == vc.size() || vc[pos + 1].a.size() != vc[pos].a.size()) {
				ok = 0;
				break;
			}
			else {
				res.emplace_back(cycle{ vi(vc[pos].a.size() *2) });
				int p = 0;
				for (size_t i = 0; i < vc[pos].a.size(); i++)
				{
					res.back().a[p] = vc[pos].a[i];
					res.back().a[p+1] = vc[pos+1].a[i];
					p += 2;
				}
				pos += 2;
			}
		}
		else {
			res.emplace_back(cycle{ vi(vc[pos].a.size()) });
			int p = 0;
			int len = (int)vc[pos].a.size();
			for (size_t i = 0; i < vc[pos].a.size(); i++) {
				res.back().a[i] = vc[pos].a[p];
				p = (p - len/2 + len) % len;
			}
			pos++;
		}
	}
	if (ok) {
		vi perm = cycles2perm(res, n);
		for (size_t i = 1; i < perm.size(); i++)
		{
			cout << perm[i] << " ";
		}
	}
	else {
		cout << "-1";
	}
	return 0;
}
