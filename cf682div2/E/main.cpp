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
	ll x;
	ll y;
};

bool cmp(pt a, pt b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cw(pt a, pt b, pt c) {
	return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
	return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) > 0;
}

void convex_hull(vector<pt> & a) {
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

//ll sq(const vector<pt>& p, ll i, ll j, ll k) {
//	return (p[j].x - p[i].x)*(p[k].y - p[i].y) - (p[j].y - p[i].y)*(p[k].x - p[i].x);
//}

int main() {

	ll n, S;
	scll2(n, S);

	vector<pt> p(n);

	auto sq = [&p](ll i, ll j, ll k) {
		return (p[j].x - p[i].x)*(p[k].y - p[i].y) - (p[j].y - p[i].y)*(p[k].x - p[i].x);
	};

	fll(i, n) {
		scll2(p[i].x, p[i].y);
	}

	convex_hull(p);

	ll nn = (ll)p.size();
	ll a = 0, b=1, c=2;
	ll msx_s = 0;
	ll ma = 0, mb = 0, mc = 0;

	while (a < nn) {
		while (sq(a, b, (c + 1) % nn) > sq(a, b, c)) c = (c+1)%nn;
		while (sq(a, (b + 1)%nn, c) > sq(a, b, c)) b = (b+1)%nn;

		ll s = sq(a, b, c);
		if (s > msx_s) {
			tie(ma, mb, mc) = tie(a, b, c);
			msx_s = s;
		}
		if (b >= nn) b -= nn;
		if (c >= nn) c -= nn;

		a++;
	}
/*	while (a < nn) {		while (sq(a, b, (c + 1)) > sq(a, b, c)) {			c = (c + 1);		}		while (sq(a, (b + 1), c) > sq(a, b, c)) {			b = (b + 1);		}		ll s = sq(a, b, c);		if (s > msx_s) {			msx_s = s;			tie(ma, mb, mc) = tie(a, b, c);			//ma = a;			//mb = b;			//mc = c;		}		if (b >= n) b -= nn;
		if (c >= n) c -= nn;		a++;	};*/
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