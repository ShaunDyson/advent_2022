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
    auto f = [](char x) {
        if (x >= 'a' && x <= 'z')
            return x - 'a' + 1;
        if (x >= 'A' && x <= 'Z')
            return x - 'A' + 27;
        assert(0&&"failed");
        return 0;
    };
    set<char> memo2;
    int i = 0;
    for(string line; getline(ifs, line);)
    {
        auto len = line.length();
        assert((len%2 + 1)&&"is not even");
        set<char> memo(line.begin(), next(line.begin(), len / 2));
        auto it = find_if(next(line.begin(), len / 2), line.end(), [&memo](char x) {
            return memo.count(x);
        });
        assert(it != line.end() && "cannot find it?");
        res1 += f(*it);

        set<char> memo2_tmp;
        switch ((++i) % 3)
        {
        case 0:
            copy_if(line.begin(), line.end(), inserter(memo2_tmp, memo2_tmp.begin()), [&memo2](char x) {
                return memo2.count(x);
            });
            assert(memo2_tmp.size() == 1 && "is not the only one?");
            res2 += f(*memo2_tmp.begin());
            memo2.clear();
            break;
        case 1:
            copy(line.begin(), line.end(), inserter(memo2, memo2.begin()));
            break;
        case 2:
            copy_if(line.begin(), line.end(), inserter(memo2_tmp, memo2_tmp.begin()), [&memo2](char x) {
                return memo2.count(x);
            });
            memo2 = memo2_tmp;
            break;
        default:
            assert(0&&"cannot go here");
            break;
        }    
    }
    cout << "part 1 result: " << res1 << endl;
    cout << "part 2 result: " << res2 << endl;
    return 0;
}