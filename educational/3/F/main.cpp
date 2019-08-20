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

struct seg_tree {
	struct node { ///

				  // lets consider frog as segment [n, t]
				  // n - frog number in sorted seq (may be replaced by position)
				  // t - tongue position = p + tongue_len, where p - frog position
				  // node keeps max position where gnat may be eaten
				  // frogs are sorted by its positions
				  // operations:
				  // 1. find most left frog with max >= gnat pos and frog pos >= gnat pos
				  // 2. change t - tongue tip pos
		ll max_rpos = -1; // tongue tip pos
		int n = -1; //number of the frog

					//assigns new value to the segment node
		template<typename T>
		void apply(int tl, int tr, T v) {
			n = tl;
			max_rpos = v;
		}
	};

	node unite(const node &a, const node &b) const {
		node res;
		res.max_rpos = max(a.max_rpos, b.max_rpos);
		return res;
	}

	void push(int v, int tl, int tr) { ///

	}

	void pull(int v) { //combines results from sons to parent
		tree[v] = unite(tree[v * 2], tree[v * 2 + 1]);
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
			tree[v].apply(tl, tr, a[tl]);
		else {
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm, a);
			build(v * 2 + 1, tm + 1, tr, a);
			pull(v);
		}
	}

	template<typename T>
	node get_first_more(int v, int tl, int tr, int l, int r, T val) {
		if (tl == tr) {
			if (tree[v].max_rpos >= val) 
				return tree[v];
			return node{};
		}

		node res{};
		int tm = (tl + tr) / 2;

		if (l <= tm && tree[2 * v].max_rpos >= val) {
			res = get_first_more(2 * v, tl, tm, l, r, val);
		}
		else if (r > tm && tree[2 * v + 1].max_rpos >= val) {
			res = get_first_more(2 * v + 1, tm + 1, tr, l, r, val);
		}
		else {
			return node{};
		}

		return res;
	}

	// returns number of first element in which t >= val 
	template<typename T>
	node get_first_more(int l, int r, T val) {
		return get_first_more(1, 0, n - 1, l, r, val);
	}

	//v - current tree node
	//l,r - required range
	//tl,tr - current tree node range
	template <typename... M>
	void update(int v, int tl, int tr, int l, int r, const M&... d) {
		if (l > r)
			return;
		if (l <= tl && r >= tr)
			tree[v].apply(tl, tr, d...);
		else {
			push(v, tl, tr);
			int tm = (tl + tr) / 2;
			if (l <= tm)
				update(v * 2, tl, tm, l, r, d...);
			if (r > tm)
				update(v * 2 + 1, tm + 1, tr, l, r, d...);
			pull(v);
		}
	}

	template <typename... M>
	void update(int pos, const M&... v) {
		update(1, 0, n - 1, pos, pos, v...);
	}

	int n;
	vector<node> tree;
};

/***********************/

struct frog {
	ll pos;
	ll tpos;
	int n;

	frog() {}
	frog(int n, ll pos, ll tpos) : pos(pos), tpos(tpos), n(n) {}
};

struct gnut {
	ll pos;
	ll w;
	int n;

	gnut() {}
	gnut(int n, ll pos, ll w) : pos(pos), w(w), n(n) {}
};

bool operator < (const frog& a, const frog& b) {
	return a.pos < b.pos;
}

bool operator < (const gnut& a, const gnut& b) {
	if (a.pos == b.pos) {
		return a.n < b.n;
	}
	return a.pos < b.pos;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int fn, gn;
	cin >> fn >> gn;

	vector<frog> frogs(fn);
	for (int i = 0; i < fn; i++) {
		ll pos, ton;
		cin >> pos >> ton;
		frogs[i] = frog{ i, pos, pos + ton };
	}

	vector<gnut> gnuts_list(gn);
	for (int i = 0; i < gn; i++) {
		ll pos, w;
		cin >> pos >> w;
		gnuts_list[i] = gnut(i, pos, w);
	}

	// set for gnuts
	set<gnut> gnuts; //pos, n

	sort(all(frogs));

	vector<ll> lposes;
	vector<ll> rposes;
	for (auto& f : frogs) {
		lposes.push_back(f.pos);
		rposes.push_back(f.tpos);
	}

	seg_tree tree;
	tree.build(rposes);



	vector<ll> cnt(lposes.size());

	for (auto& g : gnuts_list) {
		auto last_f = upper_bound(all(lposes), g.pos);
		if (g.pos < lposes[0]) {
			continue;
		}
		auto node = tree.get_first_more(0, (int)distance(begin(lposes), last_f) - 1, g.pos);
		if (node.max_rpos < 0) {
			gnuts.insert(g);
			continue;
		}

		// eats all gnats
		// cout << "Frog #" << node.n << " eat #" << g.n << " gnat" << endl;
		ll pos = node.max_rpos + g.w;
		cnt[node.n]++;
		while (true) {
			auto gnats_start = gnuts.lower_bound(gnut{ -1, lposes[node.n], 0 });
			auto gnats_end = gnuts.upper_bound(gnut{ INF, pos, 0 });
			if (gnats_end == gnats_start)
				break;
			for (auto i = gnats_start; i != gnats_end; ++i) {
				pos += i->w;
				cnt[node.n]++;
				// cout << "Frog #" << node.n << " eat #" << i->n << " gnat" << endl;
			}
			gnuts.erase(gnats_start, gnats_end);
		}

		rposes[node.n] = pos;
		tree.update(node.n, pos);
	}

	vector<ll> cnt_ans(lposes.size());
	vector<ll> len_ans(lposes.size());
	for (auto i = 0; i < lposes.size(); ++i) {
		cnt_ans[frogs[i].n] = cnt[i];
		len_ans[frogs[i].n] = rposes[i] - frogs[i].pos;
	}

	for (auto i = 0; i < cnt_ans.size(); ++i) {
		cout << cnt_ans[i] << " " << len_ans[i] << endl;
	}
	
	return 0;
}