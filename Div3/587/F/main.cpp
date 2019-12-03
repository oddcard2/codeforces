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

#if 1 // O(1) from 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	string s;
	cin >> n >> k >> s;

	vi mlr(n, -1);
	int lst = -1;
	forn(i, n) {
		if (s[i] == '1') {
			for (int j = lst + 1; j < min(n, i + k + 1); j++) {
				mlr[j] = i;
			}
			lst = i + k;
		}
	}
	
	vll dp(n+1, INF64);
	dp[n] = 0;

	ford(i, n) {
		dp[i] = min(dp[i], dp[i + 1] + (i + 1));
		if (mlr[i] != -1) {
			int ps = max(0, mlr[i] - k);
			dp[ps] = min(dp[ps], dp[i + 1] + mlr[i] + 1);
		}
	}

	cout << dp[0];
	return 0;
}


#else // my solution
ll progress_sum(ll a0, int d, int n) {
	ll an = a0 + d * (n - 1);
	return (a0 + an)*n / 2;
}

pair<int, int> bin_search(int n, std::function<bool(int)> ok) {
	int l = -1, r = n, mid;
	while (r - l > 1) {
		mid = (l + r) / 2;
		if (ok(mid))
			r = mid;
		else
			l = mid;
	}
	return { l,r };
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	string s;
	cin >> n >> k >> s;

	struct dps {
		ll s;
		ll e;
	};

	vector<dps> dp;
	dp.push_back(dps{ 0,-1 });

	int curr = -1; //pos of current router
	auto fn = [&](int m) {
		ll s;
		int e;
		if (m == 0) {
			e = max(-1, curr - k-1);
			s = 0;
			if (e >= 0) {
				s = progress_sum(1, 1, e+1);
			}
		}
		else {
			s = dp[m].s;
			e = dp[m].e;
		}
		// sum if take all router till m (including it)
		ll res = s;
		ll ed = min(curr + k, n - 1);
		ll st = max(e + 1, curr - k);

		res += curr+1;
		if (e + 1 < st) {
			res += progress_sum(dp[m].e + 1+1, 1, st - dp[m].e - 1);
		}
		return res;
	};

	auto fn1 = [&](int m) {
		return fn(m + 1) > fn(m);
	};

	auto calc = [&](int pos) {
		ll res;
		curr = pos;

		if (sz(dp)==1) {
			return fn(0);
		}

		auto r = bin_search(sz(dp)-1, fn1);
		res = fn(r.second);
		return res;
	};

	forn(i, sz(s)) {
		if (s[i] == '1') {
			int e = min(sz(s) - 1, i + k);
			ll s = calc(i);
			dp.push_back(dps{ s,e });
		}
	}

	ll best = INF64;

	ford(i, sz(dp)) {
		ll ans = dp[i].s;
		if (dp[i].e < n - 1) {
			ans += progress_sum(dp[i].e + 1+1, 1, n - dp[i].e - 1);
		}
		best = min(ans, best);
	}
	cout << best;
	
	return 0;
}

#endif