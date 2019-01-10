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

void sieve(int n, vector<char>& prime) {
	prime[0] = prime[1] = false;
	for (int i = 2; i*i <= n; ++i)
		if (prime[i])
			for (int j = i * i; j <= n; j += i)
				prime[j] = false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	rvn;

	vi cnt(1000000 + 1);
	int mm = 0;
	forn(i, n) {
		cnt[v[i]]++;
		if (v[i] > mm)
			mm = v[i];
	}

	int k = mm *2;
	vector<char> prime(k + 1, true);
	sieve(k, prime);

	sort(all(v));
	auto ne = unique(all(v));
	v.erase(ne, end(v));

	int a, b;
	int mx = 1;
	forn(i, sz(v)) {
		fore(j, i + 1, sz(v)) {
			int sm = v[i] + v[j];
			if (prime[sm]) {
				int c = 2;
				if (v[i] == 1) {
					c = cnt[v[i]] + 1;
				}
				else if (v[j] == 1) {
					c = cnt[v[j]] + 1;
				}
				if (c > mx) {
					a = v[i];
					b = v[j];
					mx = c;
				}
			}
		}

	}
	

	
	if (mx == 1 || cnt[1] > mx) {
		int a = v[0];
		int nn = 1;
		if (cnt[1] > 0) {
			a = 1;
			nn = cnt[1];
		}
		cout << nn << '\n';
		forn(i,nn)
			cout << a << " ";
	}
	else {
		if (a > b)
			swap(a, b);
		int nn = (a == 1) ? cnt[a] : 1;
		cout << nn + 1 << '\n';
		forn(i, nn) {
			cout << a << " ";
		}
		cout << b << " ";
	}
	
	return 0;
}