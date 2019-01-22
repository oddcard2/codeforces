#include "bits/stdc++.h"

using namespace std;

////////////

const int mod = 1000000007;

template<typename T>
inline int add(T a, T b) { return a + b >= mod ? a + b - mod : a + b; }
template<typename T>
inline void inc(T& a, T b) { a = add(a, b); }
template<typename T>
inline int sub(T a, T b) { return a - b < 0 ? a - b + mod : a - b; }
template<typename T>
inline void dec(T& a, T b) { a = sub(a, b); }

typedef long long ll;
typedef long double ld;

typedef vector<int> vi;

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

////////////

/***********************/
template<typename T>
T gcdex(T a, T b, T & x, T & y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	T x1, y1;
	T d = gcdex(b%a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

template<typename T>
bool find_any_solution(T a, T b, T c, T & x0, T & y0, T & g) {
	g = gcdex(abs(a), abs(b), x0, y0);
	if (c % g != 0)
		return false;
	x0 *= c / g;
	y0 *= c / g;
	if (a < 0)   x0 *= -1;
	if (b < 0)   y0 *= -1;
	return true;
}
/***********************/

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

	ll a1, b1, a2, b2, L, R;
	cin >> a1 >> b1 >> a2 >> b2 >> L >> R;

	//a1,a2>0
	ll a = a1, b = -a2, c = b2 - b1;
	//a>0, b<0

	ll k0, l0, g;
	find_any_solution(a, b, c, k0, l0, g);

	//-a/g < 0
	//b/g = (-a2)/g < 0

	//find k when x,y >= 0
	ll maxk1 = (k0 * g) / (-b);
	if (maxk1*b / g + k0 < 0) {
		if ((maxk1 - 1)*b / g + k0 >= 0) {
			maxk1--;
		}
		else if ((maxk1 + 1)*b / g + k0 >= 0) {
			maxk1++;
		}
	}
	ll maxk2 = (l0*g) / a;
	if (maxk2*(-a) / g + l0 < 0) {
		if ((maxk2 - 1)*(-a) / g + l0 >= 0) {
			maxk2--;
		}
		else if ((maxk2 + 1)*(-a) / g + l0 >= 0) {
			maxk2++;
		}
	}
	ll maxk = min(maxk1, maxk2);

	//finds k bound for L then for R

	ll coef = -a / g;
	ll start_bound = maxk;

	ll step = 1;

	ll startk = maxk, endk = maxk;
	if (a2*(start_bound*coef + l0) + b2 < L) {
		while (a2*(start_bound*coef + l0) + b2 < L) {
			start_bound -= step;
			step *= 2;
		}

		auto res = bin_search<ll>(-(start_bound - maxk), [&](ll v) {
			ll y = (start_bound + v) * coef + l0;
			return a2*y+b2  <= L;
		});
		startk = start_bound + res.first;
	}

	//return 0;
	ll end_bound = maxk;
	if (a2*(end_bound*coef + l0) + b2 < R) {
		step = 1;
		end_bound = start_bound;
		while (a2*(end_bound*coef + l0) + b2 < R) {
			end_bound -= step;
			step *= 2;
		}

		auto res = bin_search<ll>(-(end_bound - maxk), [&](ll v) {
			ll y = (end_bound + v) * coef + l0;
			return a2 * y + b2 <= R;
		});
		endk = end_bound + res.second;
	}
	else {
		cout << "0";
		return 0;
	}

	cout << -(endk - startk) + 1;
	
	return 0;
}