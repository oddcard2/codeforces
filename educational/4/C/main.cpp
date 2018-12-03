#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string s;
	cin >> s;

	bool ok = true;
	int cnt = 0;
	stack<char> st;

	for (auto i = 0; i < s.size(); i++)
	{
		auto c = s[i];
		if (c == '(' || c == '{' || c == '[' || c == '<') {
			st.push(c);
		}
		if (c == ')' || c == '}' || c == ']' || c == '>') {
			if (st.empty()) {
				ok = false;
				break;
			}
			auto oc = st.top();
			st.pop();

			if (!((oc == '(' && c == ')') || (oc == '[' && c == ']') || (oc == '{' && c == '}') || (oc == '<' && c == '>'))) {
				cnt++;
			}
		}
	}
	if (!st.empty())
		ok = false;
	
	if (!ok)
		cout << "Impossible";
	else
		cout << cnt;
	return 0;
}