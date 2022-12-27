#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <set>
#include <stack>
    void getinfo(std::vector<int>& memo1, std::vector<std::vector<int>>& memo2)
    {
        std::map<std::string, int> indexs;
        std::map<std::string, int> rates;
        std::map<std::string, std::vector<std::string>> tunnels;
        // std::ifstream ifs("day16_t.txt");
        std::ifstream ifs("day16.txt");
        for(std::string line;std::getline(ifs,line);)
        {
            // std::cout << line << "\n";
            auto first=line.begin()+6,last=line.end(),it(first);
            it=std::find(first,last,' ');
            std::string x(first,it);
            first=std::find(first,last,'=')+1;
            it=std::find(first,last,';');
            rates[x]=std::stoi(std::string(first,it));
            it+=23;
            if (*it!='s')--it;
            do {
                first=it+2;
                it=std::find(first,last,',');
                tunnels[x].push_back(std::string(first, it));
            } while (it!=last);
        }
        for (auto x:rates)
            std::cout << x.first << ":"<<x.second<<",";
        std::cout <<"\n";
        for (auto x:tunnels)
        {
            std::cout << x.first<<":";
            for(auto y:x.second)
                std::cout << y << "|";
            std::cout << ",";
        }
        std::cout<< "\n";
        auto n = rates.size();
        auto it = rates.begin();
        for (int i = 0; i < n; ++i)
        {
            indexs[it->first] = i;
            memo1.push_back(it->second);
            ++it;
        }
        std::fill_n(std::back_inserter(memo2), memo1.size(), std::vector<int>(memo1.size(),0));
        for (auto x : rates)
        {
            std::map<std::string,int> s1;
            std::queue<std::string> q1;
            q1.push(x.first);
            int i1=0;
            while (!q1.empty())
            {
                auto n1=q1.size();
                while(n1--)
                {
                    auto v=q1.front();
                    q1.pop();
                    if (s1.count(v)) continue;;
                    s1[v]=i1;
                    memo2[indexs[x.first]][indexs[v]]=i1;
                    for (auto x:tunnels[v])
                    {
                        q1.push(x);
                    }
                }
                ++i1;
            }
            std::cout<<x.first<<":";
            for (auto p:s1)
                std::cout<<p.first<<" with " <<p.second << ",";
            std::cout << "\n";
        }
    }

int main(int argc, char const *argv[])
{
    // you are at ??
    // you can open it or move to ?
    std::vector<int> memo1;
    std::vector<std::vector<int>> memo2;
    getinfo(memo1,memo2);
    {
        int n = 30;
        std::vector<std::map<std::string, int>> memo(n + 1, std::map<std::string, int>());
        for (auto x:memo1)
            std::cout << x << ",";
        std::cout<<"\n";
        for (auto x:memo2)
        {
            for (auto y:x)
                std::cout<<y<<",";
        std::cout<<"\n";
        }
    }
    auto f = [&](int _n, std::vector<int> &inds) {
        auto res(0);
        do
        {
            int n(_n), count(0);
            auto first = inds.begin(), last = inds.end();
            // count+=(n-=2)*memo1[*first];
            while (++first != last)
            {
                n -= memo2[*(first - 1)][*first] + 1;
                if (n <= 0)
                    break;
                count += n * memo1[*first];
            }
            // if (res < count) //||(!(ii++%1'000'000)))
            // {
            //     for (auto x : inds)
            //         std::cout << x << "->";
            //     std::cout << count << "|" << res << "\n";
            // }
            res = std::max(res, count);
            if (first != last)
                std::sort(++first, last, std::greater<int>());
        } while (std::next_permutation(inds.begin() + 1, inds.end()));
        return res;
    };
    std::vector<int> inds={0};
    auto n=memo2.size();
    for (auto i=0;i<n;++i)
    {
        if (memo1[i])
            inds.push_back(i);
    }
    int res(0),ii(0);
    int a(0);
    do {
        std::vector<bool> m1(inds.size(),true);
        ++a;
        for (int i=1;i<a;++i)
        {
            m1[i]=false;
        }
        do {
            std::vector<int> inds1 = {0};
            std::vector<int> inds2 = {0};
            for (int i=1;i<inds.size();++i)
            {
                if(m1[i])
                    inds1.push_back(inds[i]);
                else
                    inds2.push_back(inds[i]);
            }
            auto r1=f(26,inds1);
            auto r2=f(26,inds2);
            if (r1+r2>res)
            {
            for (auto x : inds1)
                std::cout << x << "->";
            std::cout << r1 << "\n";
            // std::cout << count << "|" << res << "\n";
            for (auto x : inds2)
                std::cout << x << "->";
            std::cout << r2 << "\n";
            }
            res = std::max(res,r1+r2);
            // std::cout << count << "|" << res << "\n";
        } while (std::next_permutation(m1.begin()+1,m1.end()));
    } while (a<inds.size()/2+1);
    std::cout << res << "\n";
    return 0;
}
