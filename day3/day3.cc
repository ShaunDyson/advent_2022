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
    auto f = [](char x) {
        if (x >= 'a' && x <= 'z')
            return x - 'a' + 1;
        if (x >= 'A' && x <= 'Z')
            return x - 'A' + 27;
        assert(0&&"failed");
        return 0;
    };
    for(string line; getline(ifs, line);)
    {
        auto len = line.length();
        assert((len%2 + 1)&&"is not even");
        set<char> memo(line.begin(), next(line.begin(), len / 2));
        auto it = find_if(next(line.begin(), len / 2), line.end(), [&memo](char x) {
            return memo.count(x);
        });
        assert(it != line.end() && "cannot find it?");
        cout << "*it is " << *it << " and " << f(*it) << endl;
        res1 += f(*it);
    }
    cout << "part 1 result: " << res1 << endl;
    return 0;
}