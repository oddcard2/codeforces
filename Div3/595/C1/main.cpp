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

template<typename T>
pair<T, T> bin_search(T n, std::function<bool(T)> ok) {
	T l = -1, r = n, mid;
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

	vll d;

	ll val = 1;
	do {
		d.push_back(val);
		val *= 3;
	} while (val <= ll(3e18));

	auto get_val = [&](ll mask, int mask_len) {
		ll res = 0;
		forn(b, mask_len) {
			if (mask & (1ll << b)) {
				res += d[b];
			}
		}
		return res;
	};

	// cout << "test = " << get_val(7, 4) << '\n';

	int q; cin >> q;
	forn(k, q) {
		ll n; cin >> n;

		auto it = std::lower_bound(all(d), n);
		if (*it == n) {
			cout << n << '\n';
			continue;
		}
		val = *it;
		
		int mask_len = (int)distance(begin(d), it) + 1;

		auto check = [&](ll mask) {
			return get_val(mask, mask_len) >= n;
		};

		auto res = bin_search<ll>((ll(1) << mask_len), check);
		cout << get_val(res.second, mask_len) << '\n';
	}

	return 0;
}


#if 0
template<typename T>
void init_bits(vector<T>& vals, vector<T>& bit_vals, int bits_count, int offset = 0) {
	for (T b = 0; b < (T)bits_count; b++) {
		vals[T(1) << b] = bit_vals[b + offset];
	}
}

template<typename T>
void mask_recalc(int mask_len, vector<T>& vals) {
	T all_bits_mask = ((T(1) << mask_len) - 1);
	for (T v = 1; v < (T(1) << mask_len); v++) {
		for (T b = 0; b < (T)mask_len; b++) {
			if (v & (T(1) << b)) {
				vals[v] = vals[(v & ~(T(1) << b)) & all_bits_mask] + vals[(T(1) << b)];
				break;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	vll d;

	ll val = 1;
	do {
		d.push_back(val);
		val *= 3;
	} while (val <= ll(3e18));

	int q; cin >> q;
	forn(k, q) {
		ll n; cin >> n;

		val = n;
		auto it = std::lower_bound(all(d), val);
		if (*it == n) {
			cout << n << '\n';
			continue;
		}
		val = *it;
		int num = (int)distance(begin(d), it)+1;
		int half1 = num / 2;
		int half2 = num - half1;
		
		vll hv1(1 << half1);
		vll hv2(1 << half2);

		init_bits(hv1, d, half1, 0);
		init_bits(hv2, d, half2, half1);

		mask_recalc(half1, hv1);
		mask_recalc(half2, hv2);

		sort(all(hv2));
		ll best = val;
		forn(i, sz(hv1)) {
			if (hv1[i] == n) {
				best = n;
				break;
			}
			if (hv1[i] > n) {
				best = min(best, hv1[i]);
			}
			else {
				ll diff = n - hv1[i];
				it = std::lower_bound(all(hv2), diff);
				if (it != end(hv2)) {
					best = min(best, hv1[i] + *it);
				}
			}
		}

		cout << best << '\n';
	}
	
	return 0;
}
#endif
