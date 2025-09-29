#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int main()
{
	ifstream in{ "input.txt" };
	ofstream out{ "output.txt" };

	int n;
	in >> n;
	vector<int> sizes;
	for (int i = 0; i < n; i++) {
		int w, h;
		in >> w >> h;
		sizes.push_back(w);
		if (i == n - 1) sizes.push_back(h);
	}

	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
	for (int l = 2; l <= n; l++) {
		for (int i = 1; i <= n - l + 1; i++) {
			int j = i + l - 1;
			dp[i][j] = numeric_limits<int>::max();
			for (int k = i; k < j; k++) {
				dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + sizes[i - 1] * sizes[k] * sizes[j]);
			}
		}
	}

	out << dp[1][n] << endl;
}