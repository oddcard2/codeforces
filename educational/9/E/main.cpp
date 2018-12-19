#include "bits/stdc++.h"

using namespace std;

typedef long long ll;


//http://e-maxx.ru/algo/fft_multiply
/*******************************/
#ifndef M_PI
#define M_PI       3.14159265358979323846
#endif

typedef complex<double> base;

void fft(vector<base> & a, bool invert = false) {
	int n = (int)a.size();

	for (int i = 1, j = 0; i < n; ++i) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(a[i], a[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		double ang = 2 * M_PI / len * (invert ? -1 : 1);
		base wlen(cos(ang), sin(ang));
		for (int i = 0; i < n; i += len) {
			base w(1);
			for (int j = 0; j < len / 2; ++j) {
				base u = a[i + j], v = a[i + j + len / 2] * w;
				a[i + j] = u + v;
				a[i + j + len / 2] = u - v;
				w *= wlen;
			}
		}
	}
	if (invert)
		for (int i = 0; i < n; ++i)
			a[i] /= n;
}

void multiply(const vector<int> & a, const vector<int> & b, vector<int> & res) {
	vector<base> fa(a.begin(), a.end()), fb(b.begin(), b.end());
	size_t n = 1;
	while (n < max(a.size(), b.size()))  n <<= 1;
	n <<= 1;
	fa.resize(n), fb.resize(n);

	fft(fa, false), fft(fb, false);
	for (size_t i = 0; i < n; ++i)
		fa[i] *= fb[i];
	fft(fa, true);

	res.resize(n);
	for (size_t i = 0; i < n; ++i)
		res[i] = int(fa[i].real() + 0.5);
}

void carry(vector<int>& res, int n) {
	int carry_val = 0;
	for (size_t i = 0; i < n; ++i) {
		res[i] += carry_val;
		carry_val = res[i] / 10;
		res[i] %= 10;
	}
}

/*******************************/

template<typename T>
T binpow(T a, int n) {
	T res = 1;
	while (n) {
		if (n & 1)
			res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}

#if 1
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, k;
	cin >> n >> k;
	vector<int> a(n);
	int mx = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		mx = max(a[i], mx);
	}

	vector<int> p(mx + 1);
	for (int i = 0; i < n; i++) {
		p[a[i]] = 1;
	}

	n = p.size();

	int j = k;
	vector<int> res = { 1 };
	while (j) {
		if (j & 1) {
			if (j == k)
				res = p;
			else {
				multiply(res, p, res);
				for (int i = 0; i < res.size(); i++) {
					if (res[i])
						res[i] = 1;
				}
			}
		}
		multiply(p, p, p);
		for (int i = 0; i < p.size(); i++) {
			if (p[i])
				p[i] = 1;
		}
		j >>= 1;
	}

	for (int i = 0; i < res.size(); i++)
	{
		if (res[i]) {
			cout << i << " ";
		}
	}
	return 0;
}
#else
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	ll n, k;
	cin >> n >> k;
	vector<int> a(n);
	int mx = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		mx = max(a[i], mx);
	}

	vector<int> p(mx + 1);
	for (int i = 0; i < n; i++) {
		p[a[i]] = 1;
	}

	n = p.size();

	int nn = n + (k - 1)*(n - 1);


	vector<base> aa(begin(p), end(p));
	
	int sz = 1;
	while (sz < nn)  sz <<= 1;

	aa.resize(sz);

	fft(aa);

	vector<base> cc = aa;
	for (int i = 0; i < aa.size(); i++)
	{
		cc[i] = binpow(aa[i], k);
	}

	fft(cc, true);

	vector<ll> res(cc.size());
	for (size_t i = 0; i < sz; ++i)
		res[i] = ll(cc[i].real() + 0.5);

	for (int i = 0; i < res.size(); i++)
	{
		if (res[i]) {
			cout << i << " ";
		}
	}
	return 0;
}
#endif
