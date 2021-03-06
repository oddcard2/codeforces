#define _CRT_SECURE_NO_WARNINGS
//#define _SILENCE_CXX17_C_HEADER_DEPRECATION_WARNING
#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define fll(i, n) for (ll i = 0; i < (n); ++i)
#define flls(i, s, n) for (ll i = s; i < (n); ++i)
#define vll vector<ll>
#define scll(x) scanf("%I64d", &(x))
#define scll2(x, y) scanf("%I64d %I64d", &(x), &(y))
#define prll(x) printf("%I64d", x)


struct pt {
	typedef ll T;
	ll x;
	ll y;
	int i;

	pt() {}
	pt(T x, T y) :x(x), y(y) {}

	const pt& operator=(const pt& o) {
		tie(x, y, i) = tie(o.x, o.y, o.i);
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

static pt::T cross(pt a, pt b) {
	return a.x*b.y - a.y*b.x;
}

//between b-a and c-a
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

//https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C++
vector<pt> convex_hull(vector<pt> P)
{
	size_t n = P.size(), k = 0;
	if (n <= 3) return P;
	vector<pt> H(2 * n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (size_t i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (size_t i = n - 1, t = k + 1; i > 0; --i) {
		while (k >= t && cross(H[k - 2], H[k - 1], P[i - 1]) <= 0) k--;
		H[k++] = P[i - 1];
	}

	H.resize(k - 1);
	return H;
}

int main() {
	ll n;
	scll(n);

	vector<pt> p(n);

	fll(i, n) {
		scll2(p[i].x, p[i].y);
		p[i].i = (int)i + 1;
	}

	auto cmp = [](const pt& a, const pt& b) {
		bool isbtna = a.y < 0 || (a.y == 0 && a.x > 0);
		bool isbtnb = b.y < 0 || (b.y == 0 && b.x > 0);
		if (isbtna != isbtnb)
			return isbtna;
		return cross(a, b) < 0;
	};
	//3
	//-1 0
	//	10 - 1
	//	1 0
	bool ex = cmp(pt(-1, 0), pt(1, 0));
	//bool ex = cmp(pt(10, -1), pt(-1, 0));

	sort(begin(p), end(p), cmp);

	pt a = p[0], b = p[1];
	auto measure = [&](const pt& a1, const pt& b1, const pt& a2, const pt& b2) {
		pt p1(dot(a1, b1), cross(a1, b1));
		pt p2(dot(a2, b2), cross(a2, b2));

		p1.y = abs(p1.y);
		p2.y = abs(p2.y);
		return cmp(p2, p1);
	};
	for (int i = 0; i < n; i++)
	{
		int next = (i + 1) % n;
		if (measure(p[i], p[next], a, b)) {
			tie(a, b) = tie(p[i], p[next]);
		}
	}

	printf("%d %d", a.i, b.i);
	return 0;
}