#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    ifstream ifs("input.txt");
    if (!ifs.is_open())
    {
        cerr << "failed to open input.txt" << endl;
        return -1;
    }
    int cache_sum = 0, cache_max = INT32_MIN;
    for (string line; getline(ifs, line);)
    {
        if (!line.empty())
        {
            cache_sum += stoi(line);
            continue;
        }
        cache_max = max(cache_max, cache_sum);
        cache_sum = 0;
    }
    cache_max = max(cache_max, cache_sum);
    cout << "the max is " << cache_max << endl;
    return 0;
}