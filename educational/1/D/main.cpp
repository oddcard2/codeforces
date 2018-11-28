#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

#define forll(i, n) for (ll i = 0; i < (n); ++i)

#define MAX_VAL 1000000000ll


int main(int argc, char **argv) {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	string line;
	getline(cin, line);

	struct node {
		int sum;
		int comp;
	};

	vector<vector<int> > num(n, vector<int>(m)); //(x,y) -> vectex num
	vector<int> comp_sizes;

	vector<vector<int> > g;
	vector<node> vs;

	vector<string> l;
	for (int i = 0; i < n; i++)
	{
		getline(cin, line);

		l.push_back(line);
	}

	int id = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) {
			char c = l[i][j];
			if (c == '.') { //vertex!
				num[i][j] = id++;
			}
			else {
				num[i][j] = -1;
			}
		}
	}
	g.resize(id + 1);
	vs.resize(id + 1);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++) {
			char c = l[i][j];
			if (c == '.') { //vertex!
				id = num[i][j];
				int s = 0;
				if (i > 0) {
					if (l[i - 1][j] == '*')
						s++;
					if (l[i - 1][j] == '.')
						g[id].push_back(num[i - 1][j]);
				}
				if (i < n - 1) {
					if (l[i +1][j] == '*')
						s++;
					if (l[i + 1][j] == '.')
						g[id].push_back(num[i + 1][j]);
				}
				if (j > 0) {
					if (l[i][j-1] == '*')
						s++;
					if (l[i][j - 1] == '.')
						g[id].push_back(num[i][j-1]);
				}
				if (j < m - 1) {
					if (l[i][j+1] == '*')
						s++;
					if (l[i][j + 1] == '.')
						g[id].push_back(num[i][j + 1]);
				}

				vs[id].sum = s;
			}
		}
	}

	n = id + 1;

	int c = 0;
	vector<bool> used(n);
	for (int s = 0; s < n; s++)
	{
		if (used[s])
			continue;

		int comp_size = vs[s].sum;
		queue<int> q;
		q.push(s);

		vector<int> d(n), p(n);
		used[s] = true;
		vs[s].comp = c;

		p[s] = -1;
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (size_t i = 0; i < g[v].size(); ++i) {
				int to = g[v][i];
				if (!used[to]) {
					used[to] = true;
					vs[to].comp = c;
					comp_size += vs[to].sum;

					q.push(to);
					d[to] = d[v] + 1;
					p[to] = v;
				}
			}
		}
		comp_sizes.push_back(comp_size);
		c++;
	}
	
	for (int i = 0; i < k; i++)
	{
		if (k < 50000) {
			int x, y;
			cin >> x >> y;
			x--;
			y--;
			int nn = num[x][y];
			if (nn < 0)
				cout << "0" << '\n';
			else
				cout << comp_sizes[vs[nn].comp] << '\n';
		}
		else {
			cout << "0" << '\n';
		}
	}

	return 0;
}