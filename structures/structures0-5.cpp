#include <fstream>
#include <vector>
using namespace std;

int find_set(vector<int>& leaders, int x) {
	if (x == leaders[x]) return x;
	leaders[x] = find_set(leaders, leaders[x]);
	return leaders[x];
}

void make_union(int& count, vector<int>& leaders, vector<int>& sizes, int x, int y) {
	x = find_set(leaders, x);
	y = find_set(leaders, y);
	if (x != y) {
		count--;
		if (sizes[x] < sizes[y]) swap(x, y);
		leaders[y] = x;
		sizes[x] += sizes[y];
	}
}

int main() {
	ifstream in{ "input.txt" };
	ofstream out{ "output.txt" };

	int n, q;
	in >> n >> q;

	int count = n;
	vector<int> leaders(n);
	vector<int> sizes(n);
	for (int i = 0; i < n; i++) {
		sizes[i] = 1;
		leaders[i] = i;
	}

	int u, v;
	for (int i = 0; i < q; i++) {
		in >> u >> v;
		make_union(count, leaders, sizes, u - 1, v - 1);
		out << count << endl;
	}
}