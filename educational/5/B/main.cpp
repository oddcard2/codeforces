#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	//Наташа выбирает строку
	int maxc = numeric_limits<int>::min();
	for (int i = 0; i < n; i++)
	{
		int minc = numeric_limits<int>::max();
		for (int j = 0; j < m; j++)
		{
			int c;
			cin >> c;
			if (c < minc) {
				minc = c;
			}
		}

		if (minc > maxc) {
			maxc = minc;
		}

	}

	cout << maxc;

	return 0;
}