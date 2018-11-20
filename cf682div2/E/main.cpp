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

void convex_hull2(vector<pt> & a) {
	if (a.size() == 1)  return;
	sort(a.begin(), a.end(), &cmp);
	pt p1 = a[0], p2 = a.back();
	vector<pt> up, down;
	up.push_back(p1);
	down.push_back(p1);
	for (size_t i = 1; i<a.size(); ++i) {
		if (i == a.size() - 1 || cw(p1, a[i], p2)) {
			while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i]))
				up.pop_back();
			up.push_back(a[i]);
		}
		if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
			while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i]))
				down.pop_back();
			down.push_back(a[i]);
		}
	}
	a.clear();
	for (size_t i = 0; i<up.size(); ++i)
		a.push_back(up[i]);
	for (size_t i = down.size() - 2; i>0; --i)
		a.push_back(down[i]);
}


tuple<ll,ll,ll,ll> brutforce(vector<pt>& p) {
	ll n = (ll)p.size();
	ll maxs = 0;
	ll ma = 0, mb = 0, mc = 0;
	for (ll i = 0; i < n-2; i++)
	{
		for (ll j = 0; j < n-1; j++)
		{
			for (ll k = 0; k < n; k++)
			{
				ll s = abs(cross(p[i], p[j], p[k]));
				if (s > maxs) {
					maxs = s;
					tie(ma, mb, mc) = tie(i, j, k);
				}
			}
		}
	}
	return make_tuple(maxs,ma,mb,mc);
}

int main() {

	ll n, S;
	scll2(n, S);

	vector<pt> p(n);

	fll(i, n) {
		scll2(p[i].x, p[i].y);
	}

	//auto bf = brutforce(p);

	p = convex_hull(p);

	n = (ll)p.size();
	ll a = 0, b, c;
	ll max_s = 0;
	ll ma = 0, mb = 0, mc = 0;

	//reverse(begin(p), end(p));
	ll pcnt = 0;
	for (; a < n-2; a++)
	{
		//while we improve S increases c
		//then increase b
		b = a + 1;
		c = b + 1;
		for (; b < n-1; b++)
		{
			if (c < b + 1)  //JIC
				c = b + 1;
			while (c < n - 1 && cross(p[a], p[b], p[c + 1]) >= cross(p[a], p[b], p[c])) {
				c++;
				pcnt++;
			}

			ll s = cross(p[a], p[b], p[c]);
			if (s > max_s) {
				max_s = s;
				tie(ma, mb, mc) = tie(a, b, c);
			}
		}
	}

	pt na, nb, nc;
	na.x = p[ma].x + (p[mb].x - p[mc].x);
	na.y = p[ma].y + (p[mb].y - p[mc].y);

	nb.x = p[mb].x + (p[mc].x - p[ma].x);
	nb.y = p[mb].y + (p[mc].y - p[ma].y);

	nc.x = p[mc].x + (p[ma].x - p[mb].x);
	nc.y = p[mc].y + (p[ma].y - p[mb].y);

	printf("%I64d %I64d\n", na.x, na.y);
	printf("%I64d %I64d\n", nb.x, nb.y);
	printf("%I64d %I64d\n", nc.x, nc.y);

	return 0;
}