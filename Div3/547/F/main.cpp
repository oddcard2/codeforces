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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	rvn;

	vector<vi> t(n, vi(n));
	vector<tri> pos;

	forn(i, n) {
		for (int j = i; j < n; ++j) {
			if (i == j) {
				t[i][j] = v[i];
			} 
			else {
				t[i][j] = t[i][j - 1] + v[j];
			}
			pos.push_back({ t[i][j], j, i });
		}
	}

	sort(all(pos));

	vector<tri> ans;
	bool f = true;
	int best = get<0>(pos[0]);

	int k = 0;
	int start = 0;
	int bestk = 0;
	int best_start = 0;
	forn(i, sz(pos)) {
		if (!f) {
			auto s = get<0>(pos[i]);
			if (s == -5) {
				s = s;
			}
			auto prevs = get<0>(pos[i - 1]);
			if (s != prevs) {
				if (k > bestk) {
					best = prevs;
					best_start = start;
					bestk = k;
				}

				start = sz(ans);
				k = 0;
				f = true;
			}
		}
		if (f) {
			ans.push_back(pos[i]);
			k++;
			f = false;
			continue;
		}
		else {
			auto prevj = get<1>(ans[sz(ans)-1]);
			auto curri = get<2>(pos[i]);
			if (prevj < curri) {
				ans.push_back(pos[i]);
				k++;
			}
		}
	}
	if (k > bestk) {
		best = get<0>(pos[sz(pos)-1]);
		best_start = start;
		bestk = k;
	}

	cout << bestk << "\n";

	int bests = get<0>(ans[best_start]);
	for (int i = best_start; i < sz(ans); ++i) {
		auto cs = get<0>(ans[i]);
		if (cs != bests)
			break;

		cout << get<2>(ans[i]) + 1 << " " << get<1>(ans[i]) + 1 << "\n";
	}

	return 0;
}