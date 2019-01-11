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

//http://e-maxx.ru/algo/fenwick_tree
//SUM with modifications
/***********************/
struct fenwick_tree
{
	vector<int> t;
	int n;

	fenwick_tree(int nn)
	{
		n = nn;
		t.assign(n, 0);
	}

	fenwick_tree(const vector<int>& a) : fenwick_tree((int)a.size())
	{
		for (unsigned i = 0; i < a.size(); i++)
			inc(i, a[i]);
	}

	int sum(int r)
	{
		int result = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			result += t[r];
		return result;
	}

	void inc(int i, int delta)
	{
		for (; i < n; i = (i | (i + 1)))
			t[i] += delta;
	}

	int sum(int l, int r)
	{
		return sum(r) - sum(l - 1);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	struct seg {
		int l;
		int r;
		int num;
		int idr;
	};

	vector<seg> sv(n);
	
	forn(i, n) {
		cin >> sv[i].l >> sv[i].r;
		sv[i].num = i;
	}
	sort(all(sv), [](const seg& a, const seg& b) { return a.r < b.r; });
	forn(i, n) {
		sv[i].idr = i;
	}

	vector<seg> svl = sv;
	sort(all(svl), [](const seg& a, const seg& b) { return a.l < b.l; });


	fenwick_tree ft(sz(sv));

	vi ans(n);
	ford(i, sz(svl)) {
		int rid = svl[i].idr;
		ans[svl[i].num] = ft.sum(rid);
		ft.inc(rid, +1);
	}

	forn(i, n) {
		cout << ans[i] << '\n';
	}
	
	return 0;
}