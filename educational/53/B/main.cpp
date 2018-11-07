#define _CRT_SECURE_NO_WARNINGS
#include "bits/stdc++.h"

using namespace std;

int main() {

	int n;
	scanf("%d", &n);

	vector<int> p(n+1);
	for (int i = 0; i < n; i++)
	{
		int g;
		scanf("%d", &g);
		p[g] = i;
	}

	int done = 0;
	for (int i = 0; i < n; i++)
	{
		int b;
		scanf("%d", &b);

		auto elem = p[b];
		int num = max(0, elem - done + 1);
		printf("%d ", num);
		done += num;
	}

	return 0;
}