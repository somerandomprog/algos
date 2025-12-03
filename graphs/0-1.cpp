#include <fstream>
#include <vector>
using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n, m, u, v;
    in >> n >> m;
    vector<vector<bool>> mat(n, vector<bool>(n, false));

    for (int i = 0; i < m; i++) {
        in >> u >> v;
        mat[u - 1][v - 1] = true;
        mat[v - 1][u - 1] = true;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            out << mat[i][j] << " ";
        out << endl;
    }

    in.close();
    out.close();
    return 0;
}