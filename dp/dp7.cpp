#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int main()
{
	ifstream in{ "input.txt" };
	ofstream out{ "output.txt" };

	int n, t;
	in >> n;
	vector<int> arr(n), dp(n + 1, numeric_limits<int>::max());
	dp[0] *= -1;

	for (int i = 0; i < n; i++) {
		in >> t;
		int j = upper_bound(dp.begin(), dp.end(), t) - dp.begin();
		if (dp[j - 1] < t && dp[j] > t) dp[j] = t;
	}

	out << (lower_bound(dp.begin(), dp.end(), numeric_limits<int>::max()) - dp.begin() - 1) << endl;
}