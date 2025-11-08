#include <fstream>
#include <queue>
using namespace std;
#define ull unsigned long long

ull qmin(queue<ull>& leaves, queue<ull>& parents) {
	if (leaves.empty()) {
		ull result = parents.front();
		parents.pop();
		return result;
	}
	else if (parents.empty()) {
		ull result = leaves.front();
		leaves.pop();
		return result;
	}
	else {
		ull result = leaves.front() < parents.front() ? leaves.front() : parents.front();
		(leaves.front() < parents.front() ? leaves : parents).pop();
		return result;
	}
}

int main() {
	ifstream in{ "huffman.in" };
	ofstream out{ "huffman.out" };

	int n;
	in >> n;

	ull total = 0, freq;
	queue<ull> leaves, parents;

	for (int i = 0; i < n; i++) {
		in >> freq;
		leaves.push(freq);
	}
	for (int i = 0; i < n - 1; i++) {
		ull l = qmin(leaves, parents), r = qmin(leaves, parents);
		total += l + r;
		parents.push(l + r);
	}

	out << total << endl;
}