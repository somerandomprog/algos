#include <fstream>
#include <vector>
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

    vector<int> p(n, 0);
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            if (mat[i][j]) p[j] = i + 1;
        }
    }

    for (int i : p) out << i << " ";

    in.close();
    out.close();
    return 0;
}