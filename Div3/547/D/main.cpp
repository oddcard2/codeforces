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

	deque<int> rs[27];
	deque<int> ls[27];
	
	int n;
	cin >> n;

	forn(i, n) {
		char s;
		cin >> s;
		if (s == '?')
			s = 26;
		else
			s -= 'a';
		ls[s].push_back(i);
	}

	forn(i, n) {
		char s;
		cin >> s;
		if (s == '?')
			s = 26;
		else
			s -= 'a';
		rs[s].push_back(i);
	}

	vector<pii> ans;
	forn(s, 27) {
		while (sz(rs[s]) && sz(ls[s])) {
			int li = ls[s].back(); ls[s].pop_back();
			int ri = rs[s].back(); rs[s].pop_back();
			ans.push_back(mp(li, ri));
		}
		while (sz(ls[s]) && sz(rs[26])) {
			int li = ls[s].back(); ls[s].pop_back();
			int ri = rs[26].back(); rs[26].pop_back();
			ans.push_back(mp(li, ri));
		}
		while (sz(rs[s]) && sz(ls[26])) {
			int li = ls[26].back(); ls[26].pop_back();
			int ri = rs[s].back(); rs[s].pop_back();
			ans.push_back(mp(li, ri));
		}
	}
	cout << sz(ans) << '\n';
	for (auto p : ans) {
		cout << p.first+1 << " " << p.second+1 << "\n";
	}

	return 0;
}