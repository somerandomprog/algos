#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main()
{
	ifstream in{ "in.txt" };
	ofstream out{ "out.txt" };

	// x - удаление, y - вставка, z - замена
	int x, y, z;
	string a, b;
	in >> x >> y >> z >> a >> b;

	vector<vector<int>> dp(a.size() + 1, vector<int>(b.size() + 1));
	for (int i = 1; i <= a.size(); i++) dp[i][0] = i * x;
	for (int j = 1; j <= b.size(); j++) dp[0][j] = j * y;

	for (int i = 1; i <= a.size(); i++) {
		for (int j = 1; j <= b.size(); j++) {
			dp[i][j] = min(min(dp[i - 1][j] + x, dp[i][j - 1] + y), dp[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? 0 : 1) * z);
		}
	}

	out << dp[a.size()][b.size()] << endl;
}