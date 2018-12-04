#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	struct node {
		int used;
		int t;
		int c;
	};

	vector<string> lab;

	vector<vector<node>> g(n, vector<node>(m));
	vector<int> cs;

	vector<pair<int, int>> o;
	vector<pair<int, int>> w;

	vector<string> ans(n, string(m, '.'));

	for (int i = 0; i < n; i++)
	{
		string l;
		cin >> l;
		lab.push_back(l);
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (lab[i][j] == '.') {
				o.push_back({ i,j });
				g[i][j].t = 0;
			}
			else {
				w.push_back({ i,j });
				g[i][j].t = 1;
			}
		}
	}


	int comp = 0;
	int comp_s = 0;
	if (!o.empty()) {
		for (auto ov : o) {
			if (g[ov.first][ov.second].used)
				continue;

			queue<pair<int, int>> q;
			g[ov.first][ov.second].used = 1;
			g[ov.first][ov.second].c = comp;
			q.push(ov);
			comp_s = 1;
			while (!q.empty()) {
				auto v = q.front();
				q.pop();

				if (v.first > 0 && g[v.first - 1][v.second].t == 0 && !g[v.first - 1][v.second].used) {
					g[v.first - 1][v.second].used = 1;
					g[v.first - 1][v.second].c = comp;
					comp_s++;
					q.push({ v.first - 1, v.second });
				}

				if (v.first < n-1 && g[v.first + 1][v.second].t == 0 && !g[v.first + 1][v.second].used) {
					g[v.first + 1][v.second].used = 1;
					g[v.first + 1][v.second].c = comp;
					comp_s++;
					q.push({ v.first + 1, v.second });
				}

				if (v.second > 0 && g[v.first][v.second-1].t == 0 && !g[v.first][v.second-1].used) {
					g[v.first][v.second-1].used = 1;
					g[v.first][v.second-1].c = comp;
					comp_s++;
					q.push({ v.first, v.second-1 });
				}

				if (v.second < m-1 && g[v.first][v.second+1].t == 0 && !g[v.first][v.second+1].used) {
					g[v.first][v.second+1].used = 1;
					g[v.first][v.second+1].c = comp;
					comp_s++;
					q.push({ v.first, v.second+1 });
				}
			}
			cs.push_back(comp_s);
			comp++;
		}
	}

	for (auto v : w) {
		int sum = 1;
		int c1 = -1, c2 = -1, c3 = -1;
		if (v.first > 0) {
			if (g[v.first - 1][v.second].t == 0) {
				c1 = g[v.first - 1][v.second].c;
				sum += cs[c1];
			}
		}

		if (v.first < n - 1) {
			if ((g[v.first + 1][v.second].t == 0) && (g[v.first + 1][v.second].c != c1)) {
				c2 = g[v.first + 1][v.second].c;
				sum += cs[c2];
			}
		}

		if (v.second > 0) {
			int cc = g[v.first][v.second - 1].c;
			if ((g[v.first][v.second-1].t == 0) && (cc != c1) && (cc != c2)) {
				c3 = cc;
				sum += cs[c3];
			}
		}

		if (v.second < m - 1) {
			int cc = g[v.first][v.second + 1].c;
			if ((g[v.first][v.second + 1].t == 0) && (cc != c1) && (cc != c2) && (cc != c3)) {
				sum += cs[cc];
			}
		}

		ans[v.first][v.second] = '0' + sum % 10;
	}
	
	for (int i = 0; i < n; i++)
	{
		cout << ans[i] << '\n';
	}
	
	return 0;
}