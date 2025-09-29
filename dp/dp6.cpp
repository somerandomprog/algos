#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main()
{
	ifstream in{ "input.txt" };
	ofstream out{ "output.txt" };

	string s;
	in>> s;

	vector<vector<int>> dp(s.length(), vector<int>(s.length()));

	for (int i = 0; i < s.length(); i++) dp[i][i] = 1;
	for (int i = 0; i < s.length() - 1; i++) dp[i][i + 1] = s[i] == s[i + 1] ? 2: 1;

	for (int i = s.length() - 3; i >= 0; i--) {
		for (int j = i + 1; j < s.length(); j++) {
			dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] + 2 : max(dp[i + 1][j], dp[i][j - 1]);
		}	
	}

	int l = dp[0][s.length() - 1];
	out << l << endl;

	string p(l, ' ');
	int i = 0, j = s.length() - 1, sh = 0;
	while (i >= 0 && j >= 0 && dp[i][j] != 0) {
		if (s[i] == s[j]) {
			p[sh] = s[i];
			p[l - sh- 1] = s[i];
			sh++; i++; j--;
		}
		else {
			if (dp[i][j] == dp[i][j - 1]) j--;
			else if (dp[i][j] == dp[i + 1][j]) i++;
		}
	}

	out << p << endl;
}