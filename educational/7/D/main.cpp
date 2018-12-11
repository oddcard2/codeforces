#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

typedef vector<int> vi;
typedef vector<ll> vll;

typedef pair<int, int> pii;
typedef tuple<int, int, int> tri;


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
#if 1
	int n; 
	cin >> n;

	vi ans(2 * n);
	int j = 0, k = 0;

	int odds = n / 2 + (n % 2);
	int evens = n / 2;
	int odd = n % 2;

	int middle_even = (!odd) && (n > 2);
	int middle_odd = odd && (n > 2);
	for (int i = 1; i <= n; i++)
	{
		if ((i % 2) && (!middle_odd || (middle_odd && i < n))) {
			ans[j] = i;
			ans[2 * (odds - middle_odd) - j -1 + middle_odd] = i;
			j++;
		}
		else if ((i%2 == 0) && !middle_even || i < n) {
			ans[2 * odds + k - middle_odd] = i;
			ans[2 * odds + 2*(evens - middle_even) - 1 - k + middle_even - middle_odd] = i;
			k++;
		}
	}
	if (middle_odd) {
		ans[2 * n - 1] = n;
		ans[odds -1] = n;
	}
	if (middle_even) {
		ans[2 * n - 1] = n;
		ans[2 * odds + evens - 1] = n;
	}

	for (int i = 0; i < 2 * n; i++) {
		cout << ans[i] << " ";
	}
#else
	auto calc = [](const vi& v) {
		int n = (int)v.size() /2;
		vector<pii> p(n+1);
		for (int i = 0; i < 2*n; i++)
		{
			int a = v[i];
			if (!p[a].first)
				p[a].first = i + 1;
			else if (!p[a].second)
				p[a].second = i + 1;
		}

		int sum = 0;
		for (int i = 1; i <= n; i++)
		{
			int d = abs(p[i].first - p[i].second);
			sum += (n - i)*abs(d + i - n);
		}
		return sum;
	};



	//vi t = { 1,3,1,2,2,3 };
	//vi t = { 1,2,2,1,3,3,4,4 };
	//vi t = { 1,1,2,2,3,3,4,4 };
	//vi t = { 1,2,3,3,2,1,4,4,5,5 };
	//vi t = { 1,3,5,5,3,1,2,4,6,6,4,2 };
	vi t = { 1,3,5,5,3,1,2,4,6,4,2,6 };
	cout << calc(t);
#endif
	return 0;
}