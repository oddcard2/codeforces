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
#define x first
#define y second

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

	string s;
	cin >> s;

	int k;
	cin >> k;

	int na = 0, nb = 0;
	forn(i, sz(s)) {
		if (s[i] == '?') {
			na++;
		}
		else if (s[i] == '*') {
			nb++;
		}
	}
	int rlen = sz(s) - (na + nb);
	int ok = 0;
	string ans;

	if (rlen == k) {
		ok = 1;
		forn(i, sz(s)) {
			if (s[i] == '?' || s[i] == '*')
				continue;
			ans += s[i];
		}
	}
	else if (rlen < k && nb > 0) {
		ok = 2;
		int req = k - rlen;
		forn(i, sz(s)) {
			if (s[i] == '?' || s[i] == '*')
				continue;
			if (i == sz(s) - 1)
				ans += s[i];
			else if (s[i+1] == '*' && req) {
				ans += s[i];
				forn(j, req) {
					ans += s[i];
				}
				req = 0;
			} else
				ans += s[i];
		}
	}
	else if (rlen > k && (rlen - k) <= (na + nb)) {
		int req = rlen - k;
		
		forn(i, sz(s)) {
			if (s[i] == '?' || s[i] == '*')
				continue;
			if (i == sz(s) - 1)
				ans += s[i];
			else {
				if ((s[i + 1] == '?' || s[i + 1] == '*') && req) {
					req--;
				}
				else {
					ans += s[i];
				}
			}
		}
		ok = 3;
	}
	if (!ok)
		cout << "Impossible";
	else
		cout << ans;
	
	return 0;
}