#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <queue>

int main(int argc, char const *argv[])
{
    // std::ifstream ifs("day12_test.txt");
    std::ifstream ifs("day12.txt");
    if (!ifs.is_open())
        return -1;
    typedef std::vector<std::string> board_type;
    typedef std::vector<std::vector<int>> memo_type;
    board_type board;
    int i(0),ei(0),ej(0),di(0),dj(0);
    for (std::string line;std::getline(ifs,line);)
    {
        board.push_back(line);
        if (line.find('E')!=std::string::npos)
        {
            ej=line.find('E');
            ei=i;
            board[ei][ej] = 'z';
        }
        if (line.find('S')!=std::string::npos)
        {
            dj=line.find('S');
            di=i;
            board[di][dj] = 'a';
        }
        ++i;
    }
    auto m = board.size(), n = board[0].size();
    std::cout << "board size: " << m << " " << n << "\n";
    std::cout << "end  state: " << ei << " " << ej << "\n";
    memo_type memo(m,std::vector<int>(n,INT32_MAX));
    memo[ei][ej]=0;
    std::queue<int> q;
    std::set<int> s;
    q.push(ei*n+ej);
    std::vector<int> d1={-1,1,0,0};
    std::vector<int> d2={0,0,-1,1};
    int res1(INT32_MAX);
    board_type sss = board;
    while (!q.empty())
    {
        auto v=q.front();
        q.pop();
        if (s.count(v))
            continue;
        auto tmpi(v/n),tmpj(v%n);
        std::cout << "goes to " << tmpi << " " << tmpj << "\n";
        for (int p=0;p<4;++p)
        {
            if (tmpi+d1[p]<0||tmpi+d1[p]>=m||tmpj+d2[p]<0||tmpj+d2[p]>=n)
                continue;
            // std::cout << board[tmpi][tmpj] << " " << board[tmpi+d1[p]][tmpj+d2[p]] << "\n";
            // 14 12 14 13 14 14 14 15
            if (board[tmpi][tmpj] > board[tmpi+d1[p]][tmpj+d2[p]] + 1)
                continue;
            // if (board[tmpi][tmpj] > board[tmpi+d1[p]][tmpj+d2[p]])
            //     continue;
            memo[tmpi+d1[p]][tmpj+d2[p]] = std::min(memo[tmpi][tmpj]+1,memo[tmpi+d1[p]][tmpj+d2[p]]);
            // std::cout << "goes to " << (tmpi + d1[p]) << " " << (tmpj + d2[p]) << " with steps " << memo[tmpi+d1[p]][tmpj+d2[p]] << "\n";
            if (board[tmpi+d1[p]][tmpj+d2[p]] == 'a')
            {
                res1=std::min(res1, memo[tmpi+d1[p]][tmpj+d2[p]]);
            }
            sss[tmpi+d1[p]][tmpj+d2[p]]='.';
            q.push((tmpi+d1[p])*n+tmpj+d2[p]);
        }
        s.insert(v);
    }
    std::cout << "small: " << res1 << "\n";
    for (auto x:sss)
        std::cout << x << "\n";
    ifs.close();
    return 0;
}
