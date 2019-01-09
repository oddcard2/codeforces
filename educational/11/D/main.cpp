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
struct pt {
	typedef ll T;
	T x;
	T y;

	pt() {}
	pt(T x, T y) :x(x), y(y) {}

	const pt& operator=(const pt& o) {
		tie(x, y) = tie(o.x, o.y);
		return *this;
	}
};

static bool operator==(const pt& a, const pt& b) {
	return tie(a.x, a.y) == tie(b.x, b.y);
}

static pt operator+(const pt& a, const pt& b) {
	return pt(a.x + b.x, a.y + b.y);
}

static pt operator-(const pt& a, const pt& b) {
	return pt(a.x - b.x, a.y - b.y);
}

static bool operator<(const pt& a, const pt& b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

static pt::T dot(pt a, pt b) {
	return a.x*b.x + a.y*b.y;
}

// > 0, if a clockwise b, for example a=(1,0),b=(-1,1) 
static pt::T cross(pt a, pt b) {
	return a.x*b.y - a.y*b.x;
}

//between b - a and c - a
// > 0 if ab clockwise ac
static pt::T cross(pt a, pt b, pt c) {
	return cross(b - a, c - a);
}

bool cmp(pt a, pt b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw(pt a, pt b, pt c) {
	return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
	return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) > 0;
}
/***********************/

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n;
	cin >> n;

	vector<pt> v(n);
	forn(i, n) {
		cin >> v[i].x >> v[i].y;
	}

	vector<pair<pt, pt>> segments;

	forn(i, n) {
		fore(j, i + 1, n) {
			if (v[i].y == v[j].y) {
				if (v[i].x < v[j].x)
					segments.push_back({ v[i], v[j] });
				else
					segments.push_back({ v[j], v[i] });
			} else if (v[i].y < v[j].y)
				segments.push_back({ v[i], v[j] });
			else
				segments.push_back({ v[j], v[i] });
		}
	}

	auto cmp = [](const pair<pt, pt>& a, const pair<pt, pt>& b) {
		//a.first will be common
		pt aa = a.second - a.first;
		pt bb = b.second - b.first;
		auto cr = cross(aa, bb);
		if (cr != 0)
			return cr < 0;
		return ((ll)aa.x*aa.x + (ll)aa.y*aa.y) < ((ll)bb.x*bb.x + (ll)bb.y*bb.y);
	};

	auto eq = [](const pair<pt, pt>& a, const pair<pt, pt>& b) {
		pt aa = a.second - a.first;
		pt bb = b.second - b.first;
		return cross(aa, bb) == 0 && ((ll)aa.x*aa.x + (ll)aa.y*aa.y) == ((ll)bb.x*bb.x + (ll)bb.y*bb.y);
	};

	sort(all(segments), cmp);

	if (!segments.empty())
		segments.push_back(segments[0]);///

	ll pairs = 0;
	ll eqcnt = 0;
	fore(i, 1, sz(segments)+1) {
		if (i < sz(segments) && eq(segments[i - 1], segments[i])) {
			if (!eqcnt)
				eqcnt = 2;
			else
				eqcnt++;
		}
		else if (eqcnt>0) {
			pairs += eqcnt*(eqcnt-1)/2;
			eqcnt = 0;
		}
	}

	cout << pairs / 2;

	return 0;
}