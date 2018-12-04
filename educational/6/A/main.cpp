#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;

	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);
	int d1 = min(dx, dy);
	dx -= d1;
	dy -= d1;

	cout << d1 + dx + dy;

	return 0;
}