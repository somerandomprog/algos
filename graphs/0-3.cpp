#include <fstream>
#include <vector>
using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n, m, u, v;
    in >> n >> m;
    vector<vector<int>> p(n, vector<int>());

    for (int i = 0; i < m; i++) {
        in >> u >> v;
        p[u - 1].push_back(v);
        p[v - 1].push_back(u);
    }

    for (int i = 0; i < n; i++) {
        out << p[i].size() << " ";
        for (int h : p[i]) out << h << " ";
        out << endl;
    }

    in.close();
    out.close();
    return 0;
}