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

ll pos(int k, int x) {
	if (x == k)
		return 1;
	if (x > k)
		return x;
	else
		return x + 1;
}

ll fs(int k, int xi, int xj) {
	return (ll)abs(pos(k, xi) - pos(k, xj));
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);


	int n, m;
	cin >> n >> m;

	vi v(m);
	forn(i, m) {
		cin >> v[i];
	}


	multimap<int, pair<int, int>> mm;
	fore(i, 1, m) {
		if (i > 0)
			mm.insert({ v[i - 1], { v[i - 1], v[i] } });
		mm.insert({ v[i],{ v[i - 1], v[i] } });
	}

	ll s = 0;
	forn(i, m - 1) {
		s += (ll)abs(v[i] - v[i + 1]);
	}

	cout << s << " ";

	fore(i, 2, n + 1) {
		int last = i - 1;
		int curr = i;

		auto last_pairs = mm.equal_range(last);
		for (auto j = last_pairs.first; j != last_pairs.second; ++j) {
			s -= fs(last, j->second.first, j->second.second);
			s += fs(curr, j->second.first, j->second.second);
		}

		auto curr_pairs = mm.equal_range(curr);
		for (auto j = curr_pairs.first; j != curr_pairs.second; ++j) {
			if (j->second.first == last || j->second.second == last)
				continue;
			s -= fs(last, j->second.first, j->second.second);
			s += fs(curr, j->second.first, j->second.second);
		}

		cout << s << " ";
	}
	
	return 0;
}