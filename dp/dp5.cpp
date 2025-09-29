#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int main()
{	
	int n;
	cin >> n;

	vector<int> a(n);
	vector<int> b(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < n; i++) cin >> b[i];

	vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = a[i - 1] == b[j - 1] ? dp[i - 1][j - 1] + 1 : max(dp[i][j - 1], dp[i - 1][j]);
		}
	}

	cout << dp[n][n] << endl;

	deque<int> ap, bp;
	int v = dp[n][n], i = n, j = n;
	while (v != 0 && i != 0 && j != 0) {
		if (a[i - 1] == b[j - 1]) {
			ap.push_front(i - 1);
			bp.push_front(j - 1);
			i -= 1;
			j -= 1;
		}
		else {
			if (dp[i][j] == dp[i - 1][j]) i -= 1;
			else if (dp[i][j] == dp[i][j - 1]) j -= 1;
		}
	}

	for (int p : ap) cout << p << " ";
	cout << endl;
	for (int p : bp) cout << p << " ";
	cout << endl;
}