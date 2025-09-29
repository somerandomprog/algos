#include <iostream>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> arr = std::vector<int>(n);
    std::vector<int> best = std::vector<int>(n, 0);
    for (int i = 0; i < n; i++) std::cin >> arr[i];

    if (n == 1) {
        std::cout << arr[0] << std::endl << 1 << std::endl;
        return 0;
    }

    if (n == 2) {
        std::cout << -1 << std::endl;
        return 0;
    }

    best[0] = arr[0];
    best[1] = -1; best[n - 2] = -1;
    best[2] = best[0] + arr[2];

    for (int i = 3; i < n; i++) {
        if (best[i] == -1) continue;
        best[i] = std::max(best[i - 2], best[i - 3]) + arr[i];
    }

    std::cout << best[n - 1] << std::endl;

    std::vector<int> way;
    int i = n - 1;
    while (i >= 2) {
        way.push_back(i + 1);
        if (i - 3 < 0) i = i - 2;
        else i = best[i - 2] > best[i - 3] ? (i - 2) : (i - 3);
    }
    way.push_back(1);

    for (int i = 0; i < way.size(); i++) std::cout << way[way.size() - 1 - i] << " ";
    std::cout << std::endl;
}