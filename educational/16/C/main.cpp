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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;

	vi types[2];
	int cnts[2] = { 0,0 };
	forn(i, n*n) {
		int v = i + 1;
		types[v % 2].push_back(v);
	}

	vector<vi> m(n, vi(n));

	std::function<void(int, int, int)> f = [&](int t, int x, int o) {

		if (o == 0) {
			m[x][x] = types[t % 2][cnts[t % 2]];
			t++;
			return;
		}
		//row ->
		int st = t;
		int l = 2 * o + 1;
		fore(i, x, x + l-1) {
			m[x][i] = types[t % 2][cnts[t %2]];
			cnts[t % 2]++;
			t++;
		}
		fore(i, x, x + l-1) {
			m[i][x + l-1] = types[t % 2][cnts[t % 2]];
			cnts[t % 2]++;
			t++;
		}

		for (int i = x + l - 1; i>x; --i) {
			m[x + l - 1][i] = types[t % 2][cnts[t % 2]];
			cnts[t % 2]++;
			t++;
		}

		for (int i = x + l - 1; i > x; --i) {
			m[i][x] = types[t % 2][cnts[t % 2]];
			cnts[t % 2]++;
			t++;
		}

		f(t+1, x + 1, o - 1);

	};

	f((((n + 1) / 2) % 2), 0, n / 2);

	forn(i,n) {
		forn(j, n) {
			cout << m[i][j] << " ";
		}
		cout << '\n';
	}
	return 0;
}