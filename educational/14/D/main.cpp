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
vector<int> used;
vector<vector<int>> g;

vector<int> comp;
function<void(int)> dfs = [&](int v) {
	used[v] = 1;
	comp.push_back(v);
	for (auto u : g[v]) {
		if (used[u])
			continue;

		dfs(u);
	}
};

//searches component and process it
void conn_components_for_each(function<void(vi&)> cb) {
	for (int i = 0; i<sz(used); ++i)
		used[i] = false;
	for (int i = 0; i<sz(used); ++i)
		if (!used[i]) {
			comp.clear();
			dfs(i);

			cb(comp);
		}
}
/***********************/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vi p(n);
	forn(i, n)
		cin >> p[i];

	vector<pii> mm(m);
	forn(i, m) {
		cin >> mm[i].first >> mm[i].second;
	}

	sort(all(mm));
	auto ne = unique(all(mm));
	mm.erase(ne, end(mm));
	
	g.resize(n);
	forn(i, sz(mm)) {
		g[mm[i].first - 1].push_back(mm[i].second - 1);
		g[mm[i].second - 1].push_back(mm[i].first - 1);
	}

	used.resize(g.size());

	vi ans = p;
	auto cb = [&](vi& v) {
		vi vals(sz(v));

		sort(all(v));
		forn(i, sz(v)) {
			vals[i] = p[v[i]];
		}

		sort(all(vals));
		reverse(all(vals));

		forn(i, sz(v)) {
			ans[v[i]] = vals[i];
		}
	};

	conn_components_for_each(cb);

	forn(i, n) {
		cout << ans[i] << " ";
	}
	return 0;
}