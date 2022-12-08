#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <set>
#include <stack>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
    char currpath[4086] = "/";
    int n = 1;
    map<string, pair<vector<string>, int>> memo_size;
    auto help_cmd = [&currpath,&n,&memo_size](string& line) {
        if (line == "$ ls")
            return;
        if (line.substr(0, 4) == "$ cd")
        {
            auto tmp = line.substr(5);
            if (tmp == "..")
            {
                while (currpath[--n] != '/');
                if (n == 0)
                {
                    currpath[1] = '\0';
                    n = 1;
                }
                else
                    currpath[n] = '\0';
            }
            else if (tmp == "/")
            {
                currpath[1] = '\0';
                n = 1;
            }
            else
            {
                if (n^1) {
                    strcpy(currpath + n, "/");
                    ++n;
                }
                strcpy(currpath + n, tmp.c_str());
                n += tmp.length();
            }
            // cout << "@ " << currpath << endl;
            assert(strncmp(currpath, "//", 2) && "can not start with // ??");
        }
        if (line.substr(0, 4) == "$ ls")
        {
            cout << currpath << endl;
            memo_size[currpath] = make_pair(vector<string>(), 0);
        }
    };
    auto help_file = [&currpath,&memo_size](string& line) {
        memo_size[currpath].second += stoi(string(line.begin(), find(line.begin(), line.end(), ' ')));
    };
    auto help_dir = [&currpath,&memo_size](string& line) {
        // cout << "add " << line.substr(5) << " to " << currpath << endl;
        memo_size[currpath].first.push_back(line.substr(4));
    };
    ifstream ifs("input.txt");
    if (!ifs.is_open())
        return -1;
    for(string line; getline(ifs, line);)
    {
        if (line.empty()) continue;
        if (line[0] == '$')
            help_cmd(line);
        if (isdigit(line[0]))
            help_file(line);
        if (line.substr(0, 3) == "dir")
            help_dir(line);
    }

    int res = 0;
    int res2 = INT32_MAX;
    function<int(string)> bt = [&bt, &memo_size, &res, &res2](string path)
    {
        int tmp = memo_size[path].second;
        for (auto t : memo_size[path].first)
        {
            cout << (path == "/" ? (path + t) : (path + "/" + t)) << endl;
            tmp += bt((path == "/") ? (path + t) : (path + "/" + t));
        }
        if (tmp >= 1035571)
        {
            res2 = min(res2, tmp);
        }
        if (tmp <= 100000)
        {
            // ++res;
            res += tmp;
        }
        cout << path << " with " << tmp << "\n";
        return tmp;
    };
    bt("/");
    cout << res << endl;
    cout << res2 << endl;
    return 0;
}