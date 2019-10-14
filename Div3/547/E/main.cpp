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

////////////

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll H, n;
	cin >> H >> n;

	vi v(n);
	forn(i, n) {
		cin >> v[i];
	}

	ll mind = INF64;
	ll sumr = 0;
	ll s = 0;
	forn(i, n) {
		s += v[i];
		mind = min(mind, s);
		sumr += v[i];
	}

	if (H > -mind && sumr >= 0) {
		cout << "-1";
		return 0;
	}

	ll minh = -mind;
	ll k = 0;
	if (H > minh) {
		k = (ll)ceil(double(H - minh) / (-sumr));
	}
	
	ll startH = H - k * (-sumr);

	if (startH == 0) {
		startH += (-sumr);
		k--;
	}

	forn(i, n) {
		startH += v[i];
		if (startH <= 0) {
			cout << k*n+(i + 1);
			return 0;
		}
	}

	return 0;
}