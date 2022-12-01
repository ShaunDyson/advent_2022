#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
    ifstream ifs("input.txt");
    if (!ifs.is_open())
    {
        cerr << "failed to open input.txt" << endl;
        return -1;
    }
    int cache_sum = 0, cache_max = INT32_MIN;
    vector<int> memo;
    for (string line; getline(ifs, line);)
    {
        if (!line.empty())
        {
            cache_sum += stoi(line);
            continue;
        }
        cache_max = max(cache_max, cache_sum);
        memo.push_back(cache_sum);
        cache_sum = 0;
    }
    cache_max = max(cache_max, cache_sum);
    memo.push_back(cache_sum);
    partial_sort(memo.begin(), next(memo.begin(), 3), memo.end(), greater<int>());
    cout << "the max is " << cache_max << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << "the top " << i << " is " << memo[i] << endl;
    }
    cout << "total is: " << memo[0] + memo[1] + memo[2] << endl;
    return 0;
}