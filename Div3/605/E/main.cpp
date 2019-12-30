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
int n;
vector<vi> src;
vi a;
vi used;
vi ans;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	
	cin >> n;
	a.resize(n);
	used.resize(n);
	ans.resize(n);
	src.resize(n);

	fill(all(ans), INF);

	forn(i, n) {
		cin >> a[i];

		if (i + a[i] < n) src[i + a[i]].push_back(i);
		if (i - a[i] >= 0) src[i - a[i]].push_back(i);
	}

	auto solve = [&](int odd) {
		fill(all(used), 0);

		queue<int> q;
		forn(i, n) {
			if (a[i] % 2 != odd) continue;

			used[i] = 1;
			q.push(i);
		}

		int k = 1;
		int cnt = sz(q);
		int j = 0;
		while (!q.empty()) {
			if (j++ < cnt) {
				int p = q.front(); q.pop();
				for (auto u : src[p]) {
					if (used[u]) {
						continue;
					}
					if (a[u] % 2 == odd) continue;

					used[u] = 1;
					ans[u] = k;
					q.push(u);
				}
			}
			else {
				j = 0;
				cnt = sz(q);
				k++;
			}
		}
	};

	solve(0);
	solve(1);

	forn(i, n) {
		if (ans[i] >= INF) {
			cout << "-1 ";
		}
		else {
			cout << ans[i] << " ";
		}
	}
	return 0;
}