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

	struct rect {
		int x1,x2,y1,y2;
	};

	rect r1, r2, r3;
	cin >> r1.x1 >> r1.y1 >> r1.x2 >> r1.y2; //w
	cin >> r2.x1 >> r2.y1 >> r2.x2 >> r2.y2;
	cin >> r3.x1 >> r3.y1 >> r3.x2 >> r3.y2;

	// a >= b
	auto isfull = [](rect a, rect b) {
		return a.x1 <= b.x1&&a.x2 >= b.x2&&a.y1 <= b.y1&&a.y2 >= b.y2;
	};

	if (isfull(r2, r1) || isfull(r3, r1)) {
		std::cout << "NO";
		return 0;
	}

	// a >= b
	auto newr = [](rect a, rect b, rect& rr) {
		if (a.x1 <= b.x1 && a.y1 <= b.y1&&a.y2 >= b.y2) {
			rr = rect{ a.x2/*+1*/, b.x2, b.y1, b.y2 };
			return true;
		}
		if (a.x2 >= b.x2 && a.y1 <= b.y1&&a.y2 >= b.y2) {
			rr = rect{ b.x1, a.x1/*-1*/, b.y1, a.y2 };
			return true;
		}
		if (a.y1 <= b.y1 && a.x1 <= b.x1&&a.x2 >= b.x2) {
			rr =rect{ b.x1, b.x2, a.y2/* + 1*/, b.y2 };
			return true;
		}
		if (a.y2 >= b.y2 && a.x1 <= b.x1&&a.x2 >= b.x2) {
			rr = rect{ b.x1, b.x2, b.y1, a.y2/*-1*/ };
			return true;
		}
		return false;
	};

	rect rr;
	if (newr(r2, r1, rr) && isfull(r3, rr)) {
		std::cout << "NO";
		return 0;
	}

	if (newr(r3, r1, rr) && isfull(r2, rr)) {
		std::cout << "NO";
		return 0;
	}

	std::cout << "YES";
	
	return 0;
}