#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
    ifstream ifs("input.txt");
    if (!ifs.is_open())
        return -1;
    int total = 0;
    for (string line; getline(ifs, line);)
    {
        auto score1 = line[2] == 'X' ? 1 : (line[2] == 'Y' ? 2 : 3);
        auto score2 = line[0] == 'A' ? 1 : (line[0] == 'B' ? 2 : 3);
        total += score1;
        if (score1 - score2 == 0)
            total += 3;
        else if (score1 - score2 == 1 || score1 - score2 == -2)
            total += 6;
    }
    cout << "total: " << total << "\n";
    return 0;
}