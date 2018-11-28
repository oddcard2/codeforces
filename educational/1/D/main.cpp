#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define forll(i, n) for (ll i = 0; i < (n); ++i)

#define MAX_VAL 1000000000ll

struct node {
	char type; //0 - ., 1- *
	char sum;
	char used;
	int comp;
};

node field[1001][1001];


int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	string line;
	getline(cin, line);

	vector<pair<int, int>> vs;
	vector<int> comp_sizes;

	for (int i = 0; i < n; i++)
	{
		getline(cin, line);

		for (int j = 0; j < m; j++) {
			field[i][j].type = line[j] == '*';
			if (!field[i][j].type)
				vs.push_back({ i,j });
		}
	}

	int c = 0;
	auto calc = [&](int i, int j) {
		int s = 0;
		if (field[i - 1][j].type) s++;
		if (field[i + 1][j].type) s++;
		if (field[i][j-1].type) s++;
		if (field[i][j+1].type) s++;
		return s;
	};
	
	n = (int)vs.size();
	for (int s = 0; s < n; s++)
	{
		if (field[vs[s].first][vs[s].second].used)
			continue;

		int comp_size = calc(vs[s].first, vs[s].second);
		queue<pair<int,int>> q;
		q.push(vs[s]);

		field[vs[s].first][vs[s].second].used = 1;
		field[vs[s].first][vs[s].second].comp = c;

#define PROCESS(i,j)\
		if (field[i][j].type == 0 && !field[i][j].used) {\
			field[i][j].used = 1;\
			field[i][j].comp = c;\
			comp_size += calc(i, j);\
			q.push({ i,j });\
		}

		while (!q.empty()) {
			int i, j;
			tie(i,j) = q.front();
			q.pop();

			PROCESS((i - 1), j);
			PROCESS((i + 1), j);
			PROCESS((i), (j-1));
			PROCESS((i), (j+1));
		}
		comp_sizes.push_back(comp_size);
		c++;
	}
	
	for (int i = 0; i < k; i++)
	{
		int x, y;
		cin >> x >> y;
		x--;
		y--;

		if (field[x][y].type)
			cout << "0" << '\n';
		else {
			int comp = field[x][y].comp;
			cout << comp_sizes[comp] << '\n';
		}
	}

	return 0;
}