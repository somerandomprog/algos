#include <fstream>
#include <bitset>
using namespace std;

int main() {
	ifstream in{ "input.txt" };
	ofstream out{ "output.txt" };

	unsigned long long n; 
	in >> n; bitset<64> bs(n);
	for (int i = 0; i < 64; i++) if (bs[i]) out << i << endl;
}