// same as 0-6
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
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

	int n, m, q;
	in >> n >> m >> q;

	int count = n;
	vector<int> leaders(n);
	vector<int> sizes(n);
	for (int i = 0; i < n; i++) {
		sizes[i] = 1;
		leaders[i] = i;
	}

	vector<pair<int, int>> edges(m);
	vector<bool> removed(m, false);
	vector<int> queries(q);

	for (int i = 0; i < m; i++) in >> edges[i].first >> edges[i].second;
	for (int i = 0; i < q; i++) {
		in >> queries[i];
		queries[i]--;
		removed[queries[i]] = true;
	}
	for (int i = 0; i < m; i++) if (!removed[i]) make_union(count, leaders, sizes, edges[i].first - 1, edges[i].second - 1);

	string result;
	for (int i = q - 1; i >= 0; i--) {
		result += count == 1 ? '1' : '0';
		make_union(count, leaders, sizes, edges[queries[i]].first - 1, edges[queries[i]].second - 1);
	}

	reverse(result.begin(), result.end());
	out << result << endl;
}