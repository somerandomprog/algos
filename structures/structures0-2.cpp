#include <fstream>
#include <vector>
using namespace std;

bool ok(const vector<int>& it, int index) {
	int leftIndex = 2 * index;
	bool leftOk = leftIndex <= it.size() ? (it[leftIndex - 1] >= it[index - 1] && ok(it, leftIndex)) : true;
	
	int rightIndex = 2 * index + 1;
	bool rightOk = rightIndex <= it.size() ? (it[rightIndex - 1] >= it[index - 1] && ok(it, rightIndex)) : true;

	return leftOk && rightOk;
}

int main() {
	ifstream in{ "input.txt" };
	ofstream out{ "output.txt" };

	int n;
	in >> n;
	vector<int> it(n);
	for (int i = 0; i < n; i++) in >> it[i];

	out << (ok(it, 1) ? "Yes" : "No") << endl;
}