#include <fstream>
#include <vector>
using namespace std;

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    int n, u, v;
    in >> n;
    vector<int> p(n, 0);

    for (int i = 1; i < n; i++) {
        in >> u >> v;
        p[v - 1] = u;
    }

    for (int i = 0; i < n; i++) out << p[i] << " ";

    in.close();
    out.close();
    return 0;
}