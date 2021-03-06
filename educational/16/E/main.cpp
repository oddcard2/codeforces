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

	ll n, x, y;
	cin >> n >> x >> y;

	//x - add or del, y - *2
	vll a(2*n + 1, INF64);

	a[0] = 0;
	for (int i = 1; i <= n; i++) {
		a[i] = min(a[i], a[i - 1] + x);

		if (i % 2 == 0) {
			a[i] = min(a[i], a[i / 2] + y);
		}
		if (a[2 * i] > a[i] + y) {
			a[2 * i] = a[i] + y;
			//there is not more than 1 +- between doubling because in other case we can use +-1 values before doubling and it's better
			
			a[2 * i - 1] = min(a[2 * i - 1], a[2 * i] + x);

			/*for (int j = 2 * i - 1; j > i; --j) {
				if (a[j] < a[j + 1] + x)
					break;
				a[j] = min(a[j], a[j + 1] + x);
			}*/
		}
		a[i] = min(a[i], a[i+1] + x);
	}

	cout << a[n];

	return 0;
}
