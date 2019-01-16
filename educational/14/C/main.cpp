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

	string x;
	cin >> x;

	auto ppos = x.find_first_of('.');
	if (ppos == string::npos) {
		x.push_back('.');
		ppos = sz(x) - 1;
	}

	//sep by .
	string before_point = x.substr(0, ppos);
	string after_point = x.substr(ppos + 1);

	//remove zeros
	auto fnz = before_point.find_first_not_of('0');
	if (fnz == string::npos)
		before_point = "";
	else
		before_point = before_point.substr(fnz);
	int after_end = -1;
	ford(i, sz(after_point)) {
		if (after_point[i] != '0') {
			after_end = i;
			break;
		}
	}
	after_point = after_point.substr(0, after_end + 1);
	if (before_point.empty() && after_point.empty()) {
		cout << "0";
		return 0;
	}

	int degree = 0;
	auto first_not_zero_after = after_point.find_first_not_of('0');
	if (before_point.empty()) { //0.(0)aa
		before_point = after_point[first_not_zero_after];
		after_point = after_point.substr(first_not_zero_after + 1);
		degree = -((int)first_not_zero_after + 1);
	}
	else {
		after_point = before_point.substr(1) + after_point;
		degree = sz(before_point) - 1;
		before_point = before_point[0];
	}


	after_end = -1;
	ford(i, sz(after_point)) {
		if (after_point[i] != '0') {
			after_end = i;
			break;
		}
	}
	after_point = after_point.substr(0, after_end + 1);

	cout << before_point;
	if (!after_point.empty()) {
		cout << ".";
		cout << after_point;
	}
	if (degree) {
		cout << "E" << degree;
	}
	
	return 0;
}