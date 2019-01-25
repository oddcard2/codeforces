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

//http://e-maxx.ru/algo/fenwick_tree
//MIN with index
/***********************/
struct fenwick_tree_min
{
	struct node {
		typedef ll T;
		T v = INF64;
		int idx;

		inline T get() const {
			return v;
		}
	};
	inline node build_node(node::T val, int idx) {
		return node{ val, idx };
	}

	vector<node> t;
	int n;

	fenwick_tree_min(int nn)
	{
		n = nn;
		t.assign(n, {});
	}

	fenwick_tree_min(const vector<int>& a) : fenwick_tree_min((int)a.size())
	{
		for (unsigned i = 0; i < a.size(); i++)
			set(i, a[i]);
	}

	//i is range [0,n-1], calc for [0,r]
	node get(int r)
	{
		node result;
		for (; r >= 0; r = (r & (r + 1)) - 1) {
			if (t[r].get() < result.get()) {
				result = t[r];
			}
		}
		return result;
	}

	//NB: we can only INCREASE values! Because max has no inverse function
	//    for min we can only DECREASE values!
	//i is range [0,n-1]
	void set(int i, node::T val)
	{
		int idx = i;
		for (; i < n; i = (i | (i + 1))) {
			if (t[i].get() > val) { //set min
				t[i] = build_node(val, idx);
			}
		}
	}
};
/***********************/

#if 0
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, x, y;
	cin >> n >> x >> y;

	//x - add or del, y - *2
	vll a(n + 1, INF64);

	a[0] = 0;
	ll m2 = 2;
	ll am2 = min(2 * x, x + y);
	for (int i = 1; i <= n; i++) {
		if (m2 <= i) {
			m2 *= 2;
			am2 = min(m2*x, am2 + y);
		}
		a[i] = min(a[i], a[i - 1] + x);

		if (i % 2 == 0) {
			a[i] = min(a[i], a[i / 2] + y);
		}
		a[i] = min(a[i], am2 + x * (m2 - i));
	}

	cout << a[n];

	return 0;
}
#else
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, x, y;
	cin >> n >> x >> y;

	//x - add or del, y - *2
	vll a(2*n + 1, INF64);

	int len = (int)(2 * n + 1);
	fenwick_tree_min t(2 * n + 1);

	a[0] = 0;
	for (int i = 1; i <= n; i++) {
		//t.set(n-i, INF64);
		int tprefix_len = len - i - 1;
		//1. from 0 +a
		a[i] = min(a[i], a[i - 1] + x);
		//2. from i/2
		if (i % 2 == 0) {
			a[i] = min(a[i], a[i / 2] + y);
		}
		//2. from some next str -a
		auto nx = t.get(tprefix_len);
		if (nx.v != INF64) {
			int idx = len - 1 - nx.idx;
			a[i] = min(a[i], a[idx] + x * (idx - i));
		}

		//3. 2*str
		if (a[2 * i] > a[i] + y) {
			int tree_idx = len - 2 * i - 1;
			t.set(tree_idx, a[i] + y - i);
			a[2 * i] = a[i] + y;
		}
	}

	cout << a[n];
	
	return 0;
}
#endif