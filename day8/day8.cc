#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <set>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
    ifstream ifs("input.txt");
    if (!ifs.is_open())
        return -1;
    vector<string> trees;
    copy(istream_iterator<string>(ifs), istream_iterator<string>(), back_inserter(trees));
    auto m = trees.size(), n = trees[0].size();
    set<int> memo;
    int res = m + n + m + n - 4;
    for (auto i = 1; i < m - 1; ++i)
    {
        auto j = 0;
        int cache = trees[i][j];
        for (; j < n - 1; ++j)
        {
            if (trees[i][j] > cache)
            {
                memo.insert(i * n + j);
                cache = trees[i][j];
            }
        }
    }
    for (auto i = 1; i < m - 1; ++i)
    {
        auto j = n - 1;
        int cache = trees[i][j];
        for (; j > 0; --j)
        {
            if (trees[i][j] > cache)
            {
                memo.insert(i * n + j);
                cache = trees[i][j];
            }
        }
    }
    for (auto j = 1; j < n - 1; ++j)
    {
        auto i = 0;
        int cache = trees[i][j];
        for (; i < m - 1; ++i)
        {
            if (trees[i][j] > cache)
            {
                memo.insert(i * n + j);
                cache = trees[i][j];
            }
        }
    }
    for (auto j = 1; j < n - 1; ++j)
    {
        auto i = m - 1;
        int cache = trees[i][j];
        for (; i > 0; --i)
        {
            if (trees[i][j] > cache)
            {
                memo.insert(i * n + j);
                cache = trees[i][j];
            }
        }
    }
    cout << res + memo.size() << endl;
    int res2 = INT32_MIN;
    for (int i = 1; i < m - 1; ++i)
    {
        for (int j = 1; j < n - 1; ++j)
        {
            auto height = trees[i][j];
            int k;
            int top(1), down(1), left(1), right(1);
            k = i;
            while (trees[--k][j] < height && k != 0)
                ++top;
            k = i;
            while (trees[++k][j] < height && k != m - 1)
                ++down;
            k = j;
            while (trees[i][--k] < height && k != 0)
                ++left;
            k = j;
            while (trees[i][++k] < height && k != n - 1)
                ++right;
            res2 = max(res2, top * down * left * right);
        }
    }
    cout << res2 << endl;
    return 0;
}