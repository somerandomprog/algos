#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
#define ll long long

ll sum(vector<ll>& f, int pos) {	
	ll result = 0;
	for (; pos >= 0; pos = (pos & (pos + 1)) - 1) result += f[pos];
	return result;
}

void add(vector<ll>& a, vector<ll>& f, int pos, ll by) {
	a[pos]++;
	for (; pos < a.size(); pos |= pos + 1) f[pos] += by;
}

int main() {
	int n, q, idx;
	cin >> n;
	
	vector<ll> a(n), f(n);
	ll v, x, l, r;
	for (int i = 0; i < n; i++) {
		cin >> v;
		add(a, f, i, v);
	}

	cin >> q;
	string op;
	for (int i = 0; i < q; i++) {
		cin >> op;
		if (op == "FindSum") {
			cin >> l >> r;
			cout << sum(f, r - 1) - (l == 0 ? 0: sum(f, l - 1)) << endl;
		}
		else {
			cin >> idx >> x;
			add(a, f, idx, x);
		}
	}
}