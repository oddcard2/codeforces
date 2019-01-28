#include "bits/stdc++.h"

using namespace std;

////////////

const int mod = 1000000007;

template<typename T>
inline int add(T a, T b) { return a + b >= mod ? a + b - mod : a + b; }
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

ll m, d;
ll dp[2002][2002][2];

bool check(const string& s) {
	ll r = 0;
	forn(i, sz(s)) {
		ll c = ll(s[i] - '0');
		if ((i + 1) % 2 == 0) {
			if (c != d)
				return false;
		}
		else if (c == d)
			return false;

		r = 10 * r + c;
		if (r > m)
			r %= m;
	}
	return r % m == 0;
}

ll solve(const string& s) {
	forn(i, 2001) forn(j, 2001) forn(k, 2) dp[i][j][k] = 0;

	dp[0][0][1] = 1;
	int n = sz(s);
	fore(i, 0, n+1) { //len
		forn (j, m) { //rem
			forn(k, 2) { //prefix eq to s
				int sd = s[i] - '0';
				if (i == 0 && k == 0)
					continue;
				forn(c, 10) {
					if ((i+1) % 2 == 0 && c != d) continue;
					if ((i+1) % 2 != 0 && c == d) continue;

					if (k == 1 && c > sd)
						break;

					ll jj = 10 * j + c;
					if (jj >= m)
						jj %= m;
					int ii = i + 1;
					int kk = k == 1 && c == sd;
					dp[ii][jj][kk] += dp[i][j][k];
					if (dp[ii][jj][kk] > mod) {
						dp[ii][jj][kk] %= mod;
					}
				}
			}
		}
	}
	return dp[n][0][0] + dp[n][0][1];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	
	cin >> m >> d;
	//d - on all evens and not in odd pos!

	string a, b;
	cin >> a >> b;

	ll aa = solve(a);
	ll bb = solve(b);
	ll ans = (sub(bb, aa) + check(a)) % mod;
	
	cout << ans;
	return 0;
}