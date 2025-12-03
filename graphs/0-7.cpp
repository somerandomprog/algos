#define ull unsigned long long
#define pui pair<ull, int>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n, m, u, v, w;
    in >> n >> m;
    vector<vector<pui>> g(n, vector<pui>());
    for (int i = 0; i < m; i++) {
        in >> u >> v >> w;
        g[u - 1].push_back({ w, v - 1 });
        g[v - 1].push_back({ w, u - 1 });
    }

    vector<bool> processed(n, false);
    vector<ull> dist(n, numeric_limits<ull>::max());
    priority_queue<pui, vector<pui>, greater<pui>> pq;
    dist[0] = 0; pq.push({ 0, 0 });

    while (!pq.empty()) {
        pui p = pq.top(); pq.pop();
        if (processed[p.second]) continue;
        processed[p.second] = true;
        dist[p.second] = p.first;
        for (pui p2 : g[p.second]) {
            if (!processed[p2.second] && p.first + p2.first < dist[p2.second])
                pq.push({ p.first + p2.first, p2.second });
        }
    }

    out << dist[n - 1] << endl;

    in.close();
    out.close();
    return 0;
}