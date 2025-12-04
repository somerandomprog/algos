#define ull unsigned long long
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct job {
    ull a, b, c;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<job> jobs(n);
    for (int i = 0; i < n; i++) cin >> jobs[i].a >> jobs[i].b >> jobs[i].c;
    sort(jobs.begin(), jobs.end(), [](job& left, job& right) { return left.a < right.a; });

    // :(
    vector<ull> dp(n, 0);
    ull max_cost = 0;
    for (int i = 0; i < n; i++) {
        ull max_prev = 0;
        for (int j = 0; j < i; j++) if (jobs[i].a > jobs[j].a + jobs[j].b - 1) max_prev = max(max_prev, dp[j]);
        dp[i] = jobs[i].c + max_prev;
        max_cost = max(max_cost, dp[i]);
    }

    cout << max_cost << endl;
    return 0;
}