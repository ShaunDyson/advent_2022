#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <set>

#define _M 1e8
// #define _ROW 10
#define _ROW 2000000
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
        std::set<e_type> memo;
        std::set<e_type> memo2;
        for (auto i=0;i<n;++i)
        {
            auto d1=abs(sx[i]-bx[i])+abs(sy[i]-by[i]);
            auto d2=abs(sy[i]-_ROW);
            if (d1<d2) continue;
            for(auto k=sx[i]-(d1-d2),e=sx[i]+(d1-d2);k<=e;++k)
                memo.insert(k);
            if (by[i]==_ROW)
                memo2.insert(bx[i]);
            if (sy[i]==_ROW)
                memo2.insert(sx[i]);
        }
        // for (auto x:memo)
        //     std::cout<<x<<",";
        // std::cout<<"\n";
        // for (auto x:memo2)
        //     std::cout<<x<<",";
        // std::cout<<"\n";
        std::cout << memo.size() << ","<<memo2.size()<<","<<memo.size()-memo2.size()<<std::endl;
    }
    return 0;
}
