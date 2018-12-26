#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

//http://e-maxx.ru/algo/ukkonen
//with modifications
/***********************/
template<typename S>
struct emaxx_ukkonen {
	vector<S> s;
	int n;

	emaxx_ukkonen(int maxn) : ptr(0, 0) {

	}

	struct node {
		//[l,r)
		int l, r, par, link;
		map<S, int> next;

		node(int l = 0, int r = 0, int par = -1)
			: l(l), r(r), par(par), link(-1) {}
		//edge len to parent
		int len() { return r - l; }
		//child node for c or -1 if no child 
		int &get(S c) {
			if (!next.count(c))  next[c] = -1;
			return next[c];
		}
		bool is_leaf() { return next.empty(); }
	};
	vector<node> t;
	int sz;

	struct state {
		int v, pos; //node and offset on edge from parent)
		state(int v, int pos) : v(v), pos(pos) {}
	};
	state ptr;

	/**
	* gets state for [l,r) substring start
	* \returns state with v == -1 if no such position found
	*/
	state go(state st, int l, int r) {
		while (l < r) {
			if (st.pos == t[st.v].len()) { //need to go futher, edge is processed
				st = state(t[st.v].get(s[l]), 0);
				if (st.v == -1) //no such path for the letter s[l], stop here  
					return st;
			}
			else { //on edge
				if (s[t[st.v].l + st.pos] != s[l])
					return state(-1, -1); //no symbol s[l] in the edge
				if (r - l < t[st.v].len() - st.pos)
					return state(st.v, st.pos + r - l); //[l,r) ends on the edge
				l += t[st.v].len() - st.pos; //reads until edge end 
				st.pos = t[st.v].len(); //need to descend below
			}
		}
		return st;
	}

	/**
	* Creates new vertex on the middle of edge if required
	* \param st - vertex parent position
	*/
	int split(state st) {
		if (st.pos == t[st.v].len())
			return st.v; //point to current vertex, offset from parent = parent edge length
		if (st.pos == 0)
			return t[st.v].par; //points to parent, offset = 0
		node v = t[st.v];
		int id = sz++;
		t[id] = node(v.l, v.l + st.pos, v.par);
		t[v.par].get(s[v.l]) = id;
		t[id].get(s[v.l + st.pos]) = st.v;
		t[st.v].par = id;
		t[st.v].l += st.pos;
		return id;
	}

	int get_link(int v) {
		if (t[v].link != -1)  return t[v].link; //old vertex, so no need to update suffix link (we increased edge only)
		if (t[v].par == -1)  return 0; //root

		int to = get_link(t[v].par); //parent must have link because it's old internal node 

									 //create the new vertex on the next suffix edge if required (delayed suffix link update)
									 //we go to below reading the text to get position for splitting
		return t[v].link = split(go(state(to, t[to].len()), t[v].l + (t[v].par == 0), t[v].r));
	}

	void tree_extend(int pos) {
		for (;;) {
			state nptr = go(ptr, pos, pos + 1);
			if (nptr.v != -1) {
				ptr = nptr; //next time starts from first suffix poistion empty rule is used for which
				return; //empty rule applied
			}

			//creates new vertex if required
			int mid = split(ptr);

			//adds new leaf
			int leaf = sz++;
			t[leaf] = node(pos, n, mid);
			t[mid].get(s[pos]) = leaf;

			//go to next suffix using suffix link and updates suffix link inside if required
			ptr.v = get_link(mid);
			ptr.pos = t[ptr.v].len();
			if (!mid)
				break; //if parent of leaf is root
		}
	}

	void build_tree() {
		sz = 1;
		t.resize(2 * s.size() + 1);
		n = (int)s.size();

		for (int i = 0; i<n; ++i)
			tree_extend(i);
	}
};

ll ed5f_solve(const vector<string>& strv, const vector<int>& prv) {
	vector<int> s;

	vector<int> pr;
	int sep = 1000;
	vector<int> sz;
	for (int i = 0; i < strv.size(); i++)
	{
		for (int j = 0; j < strv[i].size() + 1; j++)
		{
			if (j < strv[i].size()) {
				s.push_back(strv[i][j]);
				sz.push_back(strv[i].size());
			}
			else {
				s.push_back(sep++);
				sz.push_back(0);
			}
			pr.push_back(prv[i]);
		}
	}


	/***********************/
	emaxx_ukkonen<int> t((int)s.size());
	t.s = move(s);
	t.build_tree();
	/***********************/
	ll mx_pr = 0;

	vector<bool> used(t.t.size()); ///t.size()!
	vector<ll> prices(t.t.size()); ///t.size()!
	int depth = 0;
	function<ll(int)> dfs_init = [&](int v) {
		used[v] = 1;

		ll res = 0;

		depth += t.t[v].len();

		bool is_leaf = t.t[v].is_leaf();
		int start = t.n - depth;
		if (is_leaf) {
			res = pr[start];
		}

		for (const auto& u : t.t[v].next) {
			if (used[u.second])
				continue;
			auto prs = dfs_init(u.second);
			res += prs;
		}

		if (!is_leaf) {
			prices[v] = res * depth;
		} else
			prices[v] = res;

		depth -= t.t[v].len();
		return res;
	};

	dfs_init(0);

	fill(begin(used), end(used), 0);

	depth = 0;
	function<void(int)> dfs_search = [&](int v) {
		used[v] = 1;

		depth += t.t[v].len();

		bool is_leaf = t.t[v].is_leaf();
		if (!is_leaf) {
			if (v > 0 && prices[v] > mx_pr)
				mx_pr = prices[v];
		}
		else {
			int start = t.t[v].l;
			ll pr = prices[v] * sz[start];
			if (pr > mx_pr) {
				mx_pr = pr;
			}
		}

		for (const auto& u : t.t[v].next) {
			if (used[u.second])
				continue;

			dfs_search(u.second);
		}

		depth -= t.t[v].len();
	};

	dfs_search(0);
	return mx_pr;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vector<string> strv(n);
	vector<int> prv(n);

	for (int i = 0; i < n; i++)
	{
		cin >> strv[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> prv[i];
	}

	ll res = ed5f_solve(strv, prv);
	cout << res;
	return 0;
}