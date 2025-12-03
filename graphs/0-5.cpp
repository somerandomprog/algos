#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n, temp;
    in >> n;
    vector<vector<bool>> mat(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            in >> temp;
            if (temp == 1) mat[i][j] = true;
        }
    }

    queue<int> q; q.emplace(0);
    vector<bool> visited(n, false);
    vector<int> marks(n, 0);

    int mark = 1;
    while (true) {
        auto it = find(marks.begin(), marks.end(), 0);
        if (it == marks.end()) break;
        int index = distance(marks.begin(), it);

        marks[index] = mark; mark++;
        visited[index] = true;
        q.emplace(index);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u = 0; u < n; u++) {
                if (mat[v][u] && !visited[u]) {
                    visited[u] = true;
                    marks[u] = mark; mark++;
                    q.emplace(u);
                }
            }
        }
    }

    for (int m : marks) out << m << " ";

    in.close();
    out.close();
    return 0;
}