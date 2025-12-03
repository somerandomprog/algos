#include <fstream>
#include <vector>
#include <stack>
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

    stack<int> s;
    vector<bool> visited(n, false);
    vector<int> marks(n, 0);

    int mark = 1;
    while (true) {
        auto it = find(visited.begin(), visited.end(), false);
        if (it == visited.end()) break;
        int index = distance(visited.begin(), it);

        s.push(index);

        while (!s.empty()) {
            int v = s.top(); s.pop();
            if (visited[v]) continue;
            visited[v] = true;
            marks[v] = mark; mark++;

            for (int u = n - 1; u >= 0; u--) {
                if (mat[v][u] && !visited[u]) s.push(u);
            }
        }
    }

    for (int m : marks) out << m << " ";

    in.close();
    out.close();
    return 0;
}