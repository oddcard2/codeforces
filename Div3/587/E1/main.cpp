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
typedef unsigned long long ull;
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

struct bb {
	ull a0;
	ull d;
	ull s;
	int n;
};

vector<bb> ps;
int mcnt = 0;
void gen_prog() {
	ps.push_back(bb{ 0,0,0,0 });
	ull an = 0;
	ull cnt = 9;
	ull ss = 0;
	fore(i, 1, 18) {	
		bb v;
		v.d = ps[i - 1].d + 1;
		v.a0 = an+v.d;

		if (1e18-ss / v.a0 < cnt) {
			v.n = 1e18 - ss / v.a0;
			mcnt += v.n;
			ps.push_back(v);
			break;
		}

		an = v.a0 + (cnt-1) * v.d;
		v.n = cnt;
		v.s = (v.a0 + an)*cnt / 2;

		ss += v.s;
		mcnt += cnt;

		cnt *= 10;
		ps.push_back(v);
		
		if (ss >= 1e18) {
			break;
		}
	}
}

template <typename T>
T progress_sum(T a0, T d, T n) {
	T an = a0 + d * (n - 1);
	return (a0 + an)*n / 2;
}

ull fs(int n) {
	ull ans = 0;
	fore(i, 1, sz(ps)) {
		if (n >= ps[i].n) {
			n -= ps[i].n;
			ans += ps[i].s;
		}
		else {
			ans += progress_sum<ull>(ps[i].a0, ps[i].d, n);
			break;
		}
	}
	return ans;
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

ull find_offset(ull pos) {
	auto res = bin_search(mcnt, [&](int p) {
		return fs(p) > pos;
	});
	return fs(res.first);
}

char get_c(ull pos) {
	ull cnt = 9;
	ull start = 1;
	fore(i, 1, 11) {
		if (pos >= i * cnt) {
			pos -= i * cnt;
		}
		else {
			ull num = start + pos / i;
			ull pp = pos % i;
			stringstream ss;
			ss << num;
			return ss.str()[pp];
		}
		cnt *= 10;
		start *= 10;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	gen_prog();

	//auto res9 = fs(9);
	//auto res10 = fs(10);

	//auto o1 = find_offset(45);
	//auto o2 = find_offset(1);
	//auto o3 = find_offset(11);

	int q; cin >> q;
	forn(qq, q) {
		ull k; cin >> k;

		auto o = find_offset(k - 1);
		auto pos = (k - 1) - o;

		cout << get_c(pos) << '\n';
	}
	return 0;
}