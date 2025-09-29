#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

int main()
{
    std::ifstream in { "input.txt" };
    std::ofstream out { "output.txt" };

    std::unordered_set<int> visited;
    std::string line;
    int value;
    long long sum = 0;
    while (std::getline(in, line)) {
        value = std::stoi(line);
        if (visited.find(value) != visited.end()) continue;
        visited.emplace(value);
        sum += value;
    }

    out << sum;
    in.close();
    out.close();
}