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

vector<vi> g;
vector<ll> sm;
vector<ll> a;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	g.resize(n+1);
	sm.resize(n+1);
	a.resize(n+1);

	forn(i, n-1) {
		int v;
		cin >> v;
		int u = i + 2;

		g[v].push_back(u);
		g[u].push_back(v);
	}

	forn(i, n) {
		int ss;
		cin >> ss;
		sm[i+1] = ss;
	}

	a[1] = sm[1];

	int s = 1;
	queue<int> q;
	q.push(s);
	vector<bool> used(n+1);
	vector<int> d(n+1), p(n+1);
	used[s] = true;
	p[s] = -1;

	bool ok = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();

		//ll chsum = -1;

		ll mins = INF64;
		for (size_t i = 0; i < g[v].size(); ++i) {
			int to = g[v][i];
			if (!used[to]) {
				if (sm[to] != -1) {
					mins = min(mins, sm[to]);
				}
			}
		}

		if (v != 1 && mins != INF64) {
			if (mins < sm[v])
			{
				ok = false;
				break;
			}
			a[v] = mins - sm[v];
			sm[v] = mins;
		}

		ll vsum = sm[v];
		for (size_t i = 0; i < g[v].size(); ++i) {
			int to = g[v][i];
			if (!used[to]) {
				used[to] = true;

				if (sm[to] != -1) {
					if (sm[to] < vsum) {
						ok = false;
						break;
					}
					/*if (chsum == -1) {
						chsum = sm[to];
					}
					else {
						if (sm[to] != chsum) {
							ok = false;
							break;
						}
					}*/
					a[to] = sm[to] - vsum;
				}
				else {
					sm[to] = vsum;
					a[to] = 0;
				}

				q.push(to);
				d[to] = d[v] + 1;
				p[to] = v;
			}
		}
		if (!ok)
			break;
	}

	if (!ok) {
		cout << "-1";
	}
	else {
		ll ans = 0;
		forn(i, sz(sm)) {
			ans += a[i];
		}
		cout << ans;
	}

	return 0;
}