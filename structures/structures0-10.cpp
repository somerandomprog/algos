#include <fstream>
#include <vector>
using namespace std;

int main() {
	ifstream in{ "input.txt" };
	ofstream out{ "output.txt" };

	int m, c, n, key;
	in >> m >> c >> n;

	auto hash = [&](int x, int i) {return ((x % m) + c * i) % m; };
	vector<int> table(m, -1);

	for (int j = 0; j < n; j++) {
		in >> key;
		int idx = hash(key, 0);
		int i = 0;

		while (true) {
			if (table[idx] == key) break;
			if (table[idx] == -1) {
				table[idx] = key;
				break;
			}
			i++; idx = hash(key, i);
		}
	}

	for (int i = 0; i < m; i++) out << table[i] << " ";
}