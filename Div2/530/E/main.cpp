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

//column stat
struct Stat {
	vi s[2] = { { 0,0,0,0 }, {0,0,0,0} };
};

vector<Stat> st;

void calc_stat(const vector<vi>& v) {
	forn(i, sz(v[0])) {
		forn(j, 2)
			forn(k, 4)
			st[i].s[j][k] = 0;
	}
	forn(i, sz(v[0])) { //columns
		forn(j, sz(v)) { //rows
			if (j % 2 == 0) {
				st[i].s[0][v[j][i]]++;
			}
			else {
				st[i].s[1][v[j][i]]++;
			}
		}
	}
}

int best = 0;
vector<vi> curr;
vector<vi> ans;

void solve(int cols) {
	vi f(2);
	vi s(2);

	forn(i, 4) {
		fore(t, i + 1, 4) {
			f[0] = i;
			f[1] = t;

			int w = 0;
			forn(k, 4) {
				if (k != f[0] && k != f[1]) {
					s[w++] = k;
				}
			}

			///
			int sum = 0;
			forn(j, cols) {
				if (j % 2 == 0) {
					if ((st[j].s[0][f[0]] + st[j].s[1][f[1]]) > (st[j].s[0][f[1]] + st[j].s[1][f[0]])) {
						curr[j][0] = f[0];
						curr[j][1] = f[1];
						sum += st[j].s[0][f[0]] + st[j].s[1][f[1]];
					}
					else {
						curr[j][0] = f[1];
						curr[j][1] = f[0];
						sum += st[j].s[0][f[1]] + st[j].s[1][f[0]];
					}
				}
				else {
					if ((st[j].s[0][s[0]] + st[j].s[1][s[1]]) > (st[j].s[0][s[1]] + st[j].s[1][s[0]])) {
						curr[j][0] = s[0];
						curr[j][1] = s[1];
						sum += st[j].s[0][s[0]] + st[j].s[1][s[1]];
					}
					else {
						curr[j][0] = s[1];
						curr[j][1] = s[0];
						sum += st[j].s[0][s[1]] + st[j].s[1][s[0]];
					}
				}
			}
			if (sum > best) {
				ans = curr;
				best = sum;
			}
		}
	}
}

vector<vi> transponse(const vector<vi>& v) {
	vector<vi> res(sz(v[0]), vi(sz(v)));
	forn(i, sz(v)) {
		forn(j, sz(v[i])) {
			res[j][i] = v[i][j];
		}
	}
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string rev = "AGCT";
	int n, m;
	cin >> n >> m;

	st.resize(m);
	curr.resize(m);
	forn(i, m)
		curr[i].resize(2);

	vector<vi> v(n, vi(m));

	forn(i, n) {
		string l;
		cin >> l;
		forn(j, sz(l)) {
			if (l[j] == 'A')
				v[i][j] = 0;
			if (l[j] == 'G')
				v[i][j] = 1;
			if (l[j] == 'C')
				v[i][j] = 2;
			if (l[j] == 'T')
				v[i][j] = 3;
		}
	}

	calc_stat(v);
	solve(m);

	int best1 = best;
	vector<vi> ans1 = ans;

	st.resize(n);
	curr.resize(n);
	forn(i, n)
		curr[i].resize(2);

	auto vt = transponse(v);
	calc_stat(vt);
	solve(n);

	if (best > best1) {
		//ans1 = transponse(ans);
		ans1 = ans;
		forn(i, n) {
			forn(j, m) {
				//res[i][j] = ;
				cout << rev[ans1[i][j % 2 != 0]];
			}
			cout << '\n';
		}
	}
	else {
		forn(i, n) {
			forn(j, m) {
				//res[i][j] = ;
				cout << rev[ans1[j][i % 2 != 0]];
			}
			cout << '\n';
		}
	}

	return 0;
}