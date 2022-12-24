#include <iostream>
#include <vector>
#include <fstream>

int main(int argc, char const *argv[])
{
    std::ifstream ifs("day10.txt");
    if (!ifs.is_open())
        return -1;
    std::vector<int> memo;
    std::string tt("");
    int cache_v = 1;
    int i = 1;
    for(std::string line; std::getline(ifs,line);)
    {
        // std::cout << line << '\n';
        if (line.size()<4)
            continue;
        else if (line.substr(0,4) == "noop")
        {
            memo.push_back(cache_v);
            // std::cout << (i++) << '\n';
        }
        else if (line.substr(0,4) == "addx")
        {
            int v = stoi(line.substr(5));
            memo.push_back(cache_v);
            // std::cout << (i++) << '\n';
            memo.push_back(cache_v);
            cache_v+=v;
            // std::cout << (i++) << " add v " << v << " to value " << cache_v << '\n';
        }
    }
    // std::cout << "memo size is " << memo.size() << '\n';
    // for (auto x : memo)
    //     std::cout << x << ',';
    // std::cout << '\n';
    ifs.close();
    int res1 = 0;
    for (auto x : {20, 60, 100, 140, 180, 220})
    {
        // std::cout << x << "," << memo[x-1] << '\n';
        res1+=memo[x-1]*x;
    }
    std::cout << "first results is " << res1 << '\n';
    auto n = memo.size();
    for(auto i(0);i<n;++i)
    {
        if(i%40+1>=memo[i]&&i%40+1<memo[i]+3)
            tt.push_back('#');
        else
            tt.push_back(' ');
    }
    std::cout << "second results is " << tt << "\n\n\n\n\n\n";
    std::cout << tt.substr(0,40) << '\n';
    std::cout << tt.substr(40,40) << '\n';
    std::cout << tt.substr(80,40) << '\n';
    std::cout << tt.substr(160,40) << '\n';
    std::cout << tt.substr(200,40) << '\n';
    return 0;
}
