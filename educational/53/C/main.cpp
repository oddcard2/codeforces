#define _CRT_SECURE_NO_WARNINGS
#include "bits/stdc++.h"

using namespace std;

typedef int64_t i64;

#define pri(x) printf("%d", (x));
#define sci(x) scanf("%d\n", &(x));
#define sci2(x, y) scanf("%d %d", &(x), &(y));

char line[200005];

int main() {
	int n,x,y;

	scanf("%d %s %d %d", &n, line, &x, &y);

	auto ok = [&](int l) {
		int x1 = 0, y1 = 0;
		for (int i = l; i < n; i++)
		{
			char d = line[i];
			if (d == 'U')
				y1++;
			if (d == 'D')
				y1--;
			if (d == 'L')
				x1--;
			if (d == 'R')
				x1++;
		}

		//int dd = (abs(x1 - x) + abs(y1 - y));
		int dd = abs(x1 - x) + abs(y1 - y);
		if (dd <= l && (dd % 2 == l % 2))
			return true;
		
		for (int i = 0; i < n-l; i++)
		{
			char d = line[i+l];
			if (d == 'U')
				y1--;
			if (d == 'D')
				y1++;
			if (d == 'L')
				x1++;
			if (d == 'R')
				x1--;

			d = line[i];
			if (d == 'U')
				y1++;
			if (d == 'D')
				y1--;
			if (d == 'L')
				x1--;
			if (d == 'R')
				x1++;

			int dd = abs(x1 - x) + abs(y1 - y);
			if (dd <= l && (dd % 2 == l % 2))
				return true;
		}

		return false; 
	};

	if (!ok(n)) {
		pri(-1);
		return 0;
	}

	int l = -1, r = n, m;
	while (r - l > 1) {
		m = (l + r) / 2;
		if (ok(m))
			r = m;
		else
			l = m;
	}

	pri(r);
	return 0;
}