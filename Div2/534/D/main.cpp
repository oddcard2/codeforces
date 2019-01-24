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

bool game() {
	//cout << "? x y" << '\n' << std::flush;
	//cin >> ans
	//ans x (x>=y) or y (x<y) or e (>60 requests)
	//! a

	//1. find segment with the only 0 inside
	int l = 0, r = 1;
	int is_more = false; //f(r) > f(l)
	string ans;
	do {
		cout << "? " << l << " " << r << '\n' << std::flush;
		cin >> ans;
		if (ans == "e")
			return false;

		is_more = ans == "y";
		if (is_more) {
			l = r;
			r *= 2;
		}
	} while (is_more);

	//2. find 2 subseq elems x1>=x2
	while (l + 1 < r) {
		int mid = (l + r) / 2;

		cout << "? " << l << " " << mid << '\n' << std::flush;
		cin >> ans;
		if (ans == "e")
			return false;

		if (ans == "x") {//l>=mid
			r = mid;
		}
		else {
			l = mid;
		}
	}

	cout << "! " << r << '\n' << std::flush;

	return true;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	while (1) {
		string cmd;
		cin >> cmd;

		if (cmd == "start") {
			if (!game())
				break;
		}
		else if (cmd == "mistake" || cmd == "end") {
			break;
		}
	}
	
	return 0;
}