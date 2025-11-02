#include <fstream>
#include <string>
#include <limits>
#include <vector>
using namespace std;

#define ll long long
ll LL_MIN = numeric_limits<long long>::min();
ll LL_MAX = numeric_limits<long long>::max();

struct node {
	ll value;
	ll minRange;
	ll maxRange;
};

int main() {
	ifstream in{ "bst.in" };
	ofstream out{ "bst.out" };
	int n;
	ll rv;
	in >> n >> rv;
	vector<node> nodes(n);
	nodes[0] = { rv, LL_MIN, LL_MAX };

	int line;
	char pos;
	ll v;
	for (int i = 1; i < n; i++) {
		in >> v >> line >> pos;
		node parent = nodes[line - 1];
		ll left = pos == 'R' ? parent.value : parent.minRange;
		ll right = pos == 'L' ? parent.value : parent.maxRange;
		if (v < left || v >= right) {
			out << "NO" << endl;
			return 0;
		}
		nodes[i] = { v, left, right };
	}
	out << "YES" << endl;
}