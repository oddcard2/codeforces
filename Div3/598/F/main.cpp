#include "bits/stdc++.h"

using namespace std;

////////////

const int mod = 1000000007;

template<typename T>
inline T add(T a, T b) { return a + b >= mod ? a + b - mod : a + b; }
template<typename T>
inline void inc(T& a, T b) { a = add(a, b); }
template<typename T>
inline T sub(T a, T b) { return a - b < 0 ? a - b + mod : a - b; }
template<typename T>
inline void dec(T& a, T b) { a = sub(a, b); }

typedef long long ll;
typedef long double ld;

typedef vector<int> vi;
typedef vector<ll> vll;

typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef tuple<int, int, int> tri;

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define ford(i, n) for (int i = int(n) - 1; i >= 0; i--)
#define fore(i, l, r) for (int i = int(l); i < int(r); i++)
#define correct(x, y, n, m) (0 <= (x) && (x) < (n) && 0 <= (y) && (y) < (m))
#define all(a) (a).begin(), (a).end()
#define sz(a) int((a).size())
#define pb(a) push_back(a)
#define mp(x, y) make_pair((x), (y))
//#define x first
//#define y second

using namespace std;

template<typename X> inline X abs(const X& a) { return a < 0 ? -a : a; }
template<typename X> inline X sqr(const X& a) { return a * a; }

const int INF = int(1e9);
const ll INF64 = ll(1e18);
const ld EPS = 1e-9, PI = 3.1415926535897932384626433832795;

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

/// DEBUG
/// https://codeforces.com/blog/entry/68809
/// TODO: compare with https://codeforces.com/blog/entry/65311

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V> &x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T &x) { int f = 0; cerr << '{'; for (auto &i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define debug(...)
#endif

////////////

//http://e-maxx.ru/algo/fenwick_tree
//SUM with modifications
/***********************/
template<typename T>
struct fenwick_tree
{
	vector<T> t;
	int n;

	fenwick_tree(int nn)
	{
		n = nn;
		t.assign(n, T(0));
	}

	fenwick_tree(const vector<T>& a) : fenwick_tree((int)a.size())
	{
		for (auto i = 0; i < a.size(); i++)
			inc(i, a[i]);
	}

	//i is range [0,n-1], calc for [0,r]
	T sum(int r)
	{
		T result = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			result += t[r];
		return result;
	}

	//i is range [0,n-1]
	void inc(int i, T delta)
	{
		for (; i < n; i = (i | (i + 1)))
			t[i] += delta;
	}

	//l,r is range [0,n-1]
	//calcs for [l,r]
	T sum(int l, int r)
	{
		return sum(r) - sum(l - 1);
	}
};
/***********************/

int perm_inv_count(const vi& a) {
	int cnt = 0;

	fenwick_tree<int> t((int)a.size());
	for (int i = 1; i < (int)a.size(); i++) {
		cnt += (a[i] - 1) - t.sum(a[i] - 1);
		t.inc(a[i], 1);
	}
	return cnt;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int q; cin >> q;

	forn(zz, q) {
		int n; cin >> n;

		string s, t;
		cin >> s; cin >> t;

		int sn[26] = { 0 };
		int tn[26] = { 0 };

		forn(i, n) {
			sn[s[i] - 'a']++;
			tn[t[i] - 'a']++;
		}

		bool dup = false;
		bool ok = true;
		forn(i, 26) {
			if (sn[i] != tn[i]) {
				ok = false;
				break;
			}
			if (sn[i] > 1) {
				dup = true;
			}
		}

		if (dup && ok) {
			cout << "YES\n";
			continue;
		}
		if (!ok) {
			cout << "NO\n";
			continue;
		}

		int ids[26];
		int id = 1;
		forn(i, 26) {
			if (sn[i]) {
				ids[i] = id++;
			}
		}

		vi perm1(n + 1);
		vi perm2(n + 1);
		forn(i, n) {
			perm1[i + 1] = ids[s[i] - 'a'];
			perm2[i + 1] = ids[t[i] - 'a'];
		}

		if ((perm_inv_count(perm1) % 2) != (perm_inv_count(perm2) % 2))
			cout << "NO\n";
		else
			cout << "YES\n";
	}
	
	return 0;
}