#include <iostream>
#include <fstream>
#include <vector>
// #include <set>
#include <algorithm>
#include "assert.h"

int main(int argc, char const *argv[])
{
    // l is the numbers
    std::vector<std::vector<int>> l;
    {
        // std::ifstream ifs("day20_test.txt");
        std::ifstream ifs("day20.txt");
        if (!ifs.is_open())
            return -1;
        int i(0);
        for (std::string line; std::getline(ifs, line);)
            l.push_back({i++,std::stoi(line)});
    }
    auto n=l.size();
    auto mix=[&l,&n](int x) {
        auto it=std::find_if(l.begin(),l.end(),[&x](std::vector<int>&y){return y[0]==x;});
        assert(it!=l.end()&&"cannot find number in mix!");
        auto p=*it;
        if (p[1]>0)
        {
            auto p0(p[1]);
            while (p0--)
            {
                if (std::next(it)!=l.end())
                {
                    std::iter_swap(it, std::next(it));
                    it=std::next(it);
                }
                else
                {
                    l.erase(it);
                    l.insert(std::next(l.begin()),p);
                    it=l.begin()+1;
                }
            }
        }
        else if (p[1]<0)
        {
            auto p0(-p[1]);
            while (p0--)
            {
                if (it==l.begin())
                {
                    l.erase(it);
                    l.insert(std::prev(l.end()),p);
                    it=std::prev(l.end(),2);
                }
                else if (it==std::next(l.begin()))
                {
                    l.erase(it);
                    l.insert(l.end(),p);
                    it=std::prev(l.end());
                }
                else
                {
                    std::iter_swap(it,std::prev(it));
                    it=std::prev(it);
                }
            }
        }
    };
    auto d1 = [&l]() {
        for (auto x : l)
            std::cout << x[1] << ",";
        std::cout<<"\n";
    };
    auto getval=[&l,&n](int x,int n0){
        auto it=std::find_if(l.begin(),l.end(),[](std::vector<int>&y){return y[1]==0;});
        assert(it!=l.end()&&"cannot find number in mix!");
        while(n0--)
        {
            ++it;
            if(it==l.end())
                it=l.begin();
        }
        return (*it)[1];
    };
    // d1();
    auto ll(l);
    for(auto x:ll) 
    {
        mix(x[0]);
        // d1();
    }
    // d1();
    std::cout<<getval(0,1000)<<","<<getval(0,2000)<<","<<getval(0,3000)<<"\n";
    std::cout<<getval(0,1000)+getval(0,2000)+getval(0,3000)<<"\n";

    // d1();
    // auto n1(1000),i(0);
    // std::vector<int> xx=l;
    // while(n1--){for(auto x:l)xx.push_back(x);}
    // n1=1000;
    // while(n1--)mix(xx[i++]);
    // d1();
    // n1=1000;
    // while(n1--)mix(xx[i++]);
    // d1();
    // n1=1000;
    // while(n1--)mix(xx[i++]);
    // d1();
    return 0;
}
