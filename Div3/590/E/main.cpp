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

/// DEBUG
/// https://codeforces.com/blog/entry/68809
/// TODO: compare with https://codeforces.com/blog/entry/65311

void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template<typename T, typename V>
void __print(const pair<T, V> &x) { cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}'; }
template<typename T>
void __print(const T &x) { int f = 0; cerr << '{'; for (auto &i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}"; }
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v) { __print(t); if (sizeof...(v)) cerr << ", "; _print(v...); }
#ifndef ONLINE_JUDGE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "] = ["; _print(__VA_ARGS__)
#else
#define debug(...)
#endif

////////////

//Copy this lines
//http://e-maxx.ru/algo/segment_tree
//with modifications
/***********************/
struct seg_tree {
	struct node { ///
		int lazy = 0;
		int color;

		uint64_t mask;

		//assigns new value to the segment node
		void apply(int col) {
			lazy = 1;
			color = col;
			mask = (1ull << col);
		}
	};

	node unite(const node &a, const node &b) const {
		node res;
		res.mask = a.mask | b.mask;
		return res;
	}

	void push(int v) { ///
		if (tree[v].lazy) {
			tree[2 * v].apply(tree[v].color);
			tree[2 * v + 1].apply(tree[v].color);
			tree[v].lazy = 0;
		}
	}

	void pull(int v) { //combines results from sons to parent
		tree[v].mask = tree[v * 2].mask | tree[v * 2 + 1].mask;
	}

	template<typename T>
	void build(const vector<T>& a) {
		n = (int)a.size();
		tree.resize(4 * n);
		build(1, 0, n - 1, a);
	}

	template<typename T>
	void build(int v, int tl, int tr, const vector<T>& a) {
		if (tl == tr)
			tree[v].apply(a[tl]);
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm, a);
			build(v * 2 + 1, tm + 1, tr, a);
			pull(v);
		}
	}

	node get(int v, int tl, int tr, int l, int r) {
		if (l <= tl && r >= tr) {
			return tree[v];
		}
		push(v);
		node res{};
		int tm = (tl + tr) / 2;

		if (r <= tm) {
			res = get(2 * v, tl, tm, l, r);
		}
		else {
			if (l > tm) {
				res = get(2 * v + 1, tm + 1, tr, l, r);
			}
			else {
				res = unite(get(2 * v, tl, tm, l, r), get(2 * v + 1, tm + 1, tr, l, r));
			}
		}
		pull(v);
		return res;
	}


	node get(int l, int r) {
		return get(1, 0, n - 1, l, r);
	}

	node get(int pos) {
		return get(1, 0, n - 1, pos, pos);
	}

	//v - current tree node
	//l,r - required range
	//tl,tr - current tree node range
	template <typename... M>
	void update(int v, int tl, int tr, int l, int r, const M&... d) {
		if (l > r)
			return;
		if (l <= tl && r >= tr)
			tree[v].apply(d...);
		else {
			push(v);
			int tm = (tl + tr) / 2;
			if (l <= tm)
				update(v * 2, tl, tm, l, r, d...);
			if (r > tm)
				update(v * 2 + 1, tm + 1, tr, l, r, d...);
			pull(v);
		}
	}

	template <typename... M>
	void update_range(int l, int r, const M&... v) {
		update(1, 0, n - 1, l, r, v...);
	}

	template <typename... M>
	void update(int pos, const M&... v) {
		update(1, 0, n - 1, pos, pos, v...);
	}

	int n;
	vector<node> tree;
};

int bit_count(uint64_t v) {
	return std::bitset<64>(v).count();
}

/***********************/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s;
	cin >> s;

	vi colors(sz(s));
	forn (i, sz(s)) {
		colors[i] = s[i] - 'a';
	}

	seg_tree t;
	t.build(colors);

	int q;
	cin >> q;

	forn(i, q) {
		int type;
		cin >> type;

		if (type == 1) {
			int pos;
			char c;
			cin >> pos >> c;

			t.update(pos - 1, c - 'a');
		}
		else {
			int l, r;
			cin >> l >> r;

			auto node = t.get(l - 1, r - 1);
			cout << bit_count(node.mask) << '\n';
		}
	}
	
	return 0;
}