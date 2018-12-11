#include "bits/stdc++.h"

using namespace std;

typedef long long ll;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string t;
	cin >> t;

	int d;
	cin >> d;

	auto pos = t.find(':');
	string h(begin(t), begin(t) + pos);
	string m(begin(t) +pos+1, end(t));

	int hh;
	int mm;
	stringstream ssh(h);
	ssh >> hh;
	stringstream ssm(m);
	ssm >> mm;

	int dh = d / 60;

	int dm = d % 60;
	mm = (mm + dm);
	if (mm >= 60) {
		mm -= 60;
		dh++;
	}

	hh = (hh+dh) % 24;

	//cout.fill('0');
	//cout.width(2);

	//cout << hh << ":" << mm;
	cout << setfill('0') << setw(2) << hh << ":" << setfill('0') << setw(2) << mm;
	return 0;
}