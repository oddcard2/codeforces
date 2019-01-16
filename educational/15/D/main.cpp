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
#if 1
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	ll d, k, a, b, t;
	cin >> d >> k >> a >> b >> t;

	ll stops = (d / k);
	if (stops && !(d % k))
		stops -= 1;
	ll ans1 = (stops)*t + (d / k)*k*a + (d % k)*a;
	ll ans2 = ans1;
	if (d > k)
		ans2 = k * a + (d - k)*b;

	stops = (d / k);
	if (stops)
		stops -= 1;
	ll ans3 = (stops)*t + (d / k)*k*a + (d % k)*b;

	ll ans = min(min(ans1, ans2), ans3);
	cout << ans;
	return 0;
}
#else //min search by binary search
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll d, k, a, b, t;
	cin >> d >> k >> a >> b >> t;

	ll max_steps = d / k + (d%k);

	auto f = [&](ll s) {
		if (s > max_steps)
			s = max_steps;

		ll stops = s ? s - 1 : 0;
	
		ll res = s * k*a;
		
		if (d >= s * k)
			res += (d - s * k)*b;
		else {
			res -= (k - (d - (s-1) * k))*a;
		}
		if (stops)
			res += t * (stops);
		return res;
	};

	ll x = -1; //steps by auto

	for (ll b = max_steps; b >= 1; b /= 2) {
		while (f(x + b) > f(x + b + 1)) x += b;
	}
	ll res = x + 1;

	cout << f(res);

	return 0;
}
#endif
