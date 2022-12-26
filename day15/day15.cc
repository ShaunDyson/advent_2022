#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>

#define _M 1e8
// #define _ROW 20
#define _ROW 4000000
typedef int e_type;
constexpr e_type _MIN=std::numeric_limits<e_type>::min();
constexpr e_type _MAX=std::numeric_limits<e_type>::max();

int main(int argc, char const *argv[])
{
    {
        std::vector<e_type> sx;
        std::vector<e_type> sy;
        std::vector<e_type> bx;
        std::vector<e_type> by;
        e_type imax(_MIN), imin(_MAX), jmax(_MIN), jmin(_MAX);
        // std::ifstream ifs("day15_t.txt");
        std::ifstream ifs("day15.txt");
        for (std::string line;std::getline(ifs,line);)
        {
            auto first=line.begin()+12,last=line.end(),it(first);
            it=find(first,last,',');
            sx.push_back(stoi(std::string(first,it)));
            imax=std::max(imax,sx.back());
            imin=std::min(imin,sx.back());
            first=it+4;
            it=find(first,last,':');
            sy.push_back(stoi(std::string(first,it)));
            jmax=std::max(jmax,sy.back());
            jmin=std::min(jmin,sy.back());
            first=it+25;
            it=find(first,last,',');
            bx.push_back(stoi(std::string(first,it)));
            imax=std::max(imax,bx.back());
            imin=std::min(imin,bx.back());
            first=it+4;
            it=find(first,last,':');
            by.push_back(stoi(std::string(first,it)));
            jmax=std::max(jmax,by.back());
            jmin=std::min(jmin,by.back());
            // std::cout << sx.back()<<","<<sy.back()<<","<<bx.back()<<","<<by.back()<<"\n";
        }
        auto n=sx.size();
        // std::vector<std::vector<char>> board(imax-imin+1,std::vector<char>(jmax-jmin+1,'.'));
        // for(auto i=0;i<n;++i)
        // {
        //     board[sx[i]-imin][sy[i]-jmin]='S';
        //     board[bx[i]-imin][by[i]-jmin]='B';
        // }
        // for (auto x:board)
        // {
        //     for(auto y:x)
        //         std::cout<<y;
        //     std::cout<<'\n';
        // }
        for (auto row=0;row<=_ROW;++row)
        {
            // std::cout << "checking row "<<row<<std::endl;
            // std::vector<bool> memo(_ROW+1,false);
            std::set<e_type> memo2;
            std::vector<std::vector<int>> memo;
            for (auto i = 0; i < n; ++i)
            {
                auto d1 = abs(sx[i] - bx[i]) + abs(sy[i] - by[i]);
                auto d2 = abs(sy[i] - row);
                if (d1 < d2)
                    continue;
                memo.push_back({std::max(sx[i] - (d1 - d2),0), std::min(sx[i] + (d1 - d2),_ROW)});
            }
            std::sort(memo.begin(),memo.end(),[](std::vector<int>&x,std::vector<int>&y){return x[0]<y[0];});
            auto m=memo.size();
            // if (memo[0][0]!=0)
            //     std::cout << "0 @ " << row<<std::endl;
            auto right(0);
            for (auto i=0;i<m;++i)
            {
                if (memo[i][0]>right+1)
                    std::cout << "@ " << row << "," << right+1 <<std::endl;
                if (memo[i][1]>right)
                    right=memo[i][1];
            }
            if (right!=_ROW)
                std::cout << "@ " << row << " over " << right << std::endl;

            // if (std::count(memo.begin(), memo.end(), true) != _ROW + 1)
            // {
            //     std::cout << "found some @ " << row << "," << std::distance(memo.begin(),find(memo.begin(),memo.end(),false))<< std::endl;
            //     std::cout << std::distance(memo.begin(),find(memo.begin(),memo.end(),false)) * 4000000 + row << '\n';
            // }
        }
        // for (auto x:memo)
        //     std::cout<<x<<",";
        // std::cout<<"\n";
        // for (auto x:memo2)
        //     std::cout<<x<<",";
        // std::cout<<"\n";
        // std::cout << memo.size() << ","<<memo2.size()<<","<<memo.size()-memo2.size()<<std::endl;
    }
    return 0;
}
