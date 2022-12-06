#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <set>

using namespace std;

int main(int argc, char** argv) {
    ifstream ifs("input.txt");
    if (!ifs.is_open())
        return -1;
    string line("");
    getline(ifs, line);
    //line = "mjqjpqmgbljsphdztnvjfqwrcgsmlb";
    int n = line.length();
    int slow = 0, fast = 14;
    for (;fast < n; slow -= 13, ++fast)
    {
        set<char> m;
        while (slow < fast) m.insert(line[slow++]);
        if (m.size() == 14) 
        {
            cout << slow << endl;
            break;
        }
    }
    return 0;
}