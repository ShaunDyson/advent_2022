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
    int res1 = 0;
    int res2 = 0;
    for(string line; getline(ifs, line);)
    {
        auto first = line.begin(), last = line.end();
        auto first2 = find(first, last, '-');
        int i0 = stoi(string(first, first2));
        first = ++first2;
        first2 = find(first, last, ',');
        int i1 = stoi(string(first, first2));
        first = ++first2;
        first2 = find(first, last, '-');
        int j0 = stoi(string(first, first2));
        int j1 = stoi(string(++first2, last));
        if ((i0 <= j0 && j1 <= i1) || (j0 <= i0 && i1 <= j1))
        {
            ++res1;
            ++res2;
            continue;
        }
        if ((i0 <= j0 && j0 <= i1) || (i0 <= j1 && j1 <= i1))
        {
            ++res2;
            continue;
        }
        if ((j0 <= i0 && i0 <= j1) || (j0 <= i1 && i1 <= j1))
        {
            ++res2;
            continue;
        }
        //cout << i0 << "," << i1 << "," << j0 << "," << j1 << "," << res1 << endl;
    }
    cout << res1 << endl;
    cout << res2 << endl;
    return 0;
}