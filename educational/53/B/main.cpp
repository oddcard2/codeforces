#define _CRT_SECURE_NO_WARNINGS
#include "bits/stdc++.h"

using namespace std;

string input = "";

int main(int argc, char **argv) {

	int n;
	scanf("%d", &n);

	vector<int> p(n+1);

	for (int i = 0; i < n; i++)
	{
		int g;
		//icp >> g;
		scanf("%d", &g);
		p[g] = i;
	}

	int done = 0;
	for (int i = 0; i < n; i++)
	{
		int b;
		//icp >> b;
		scanf("%d", &b);
		if (done == n) {
			printf("0 ");
			//cout << "0" << " ";
			continue;
		}
		
		auto elem = p[b];
		int num = elem - done + 1;
		if (num <= 0) {
			//cout << "0" << " ";
			printf("0 ");
			continue;
		}
		//cout << num << " ";
		printf("%d ", num);
		done += num;
	}

	return 0;
}