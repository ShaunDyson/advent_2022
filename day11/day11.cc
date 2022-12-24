#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <map>
#include <set>

typedef long long worry_type;

class banana {
public:
    banana(worry_type l) : _l(l) {}
    worry_type getl() {return _l;}
    void setl(worry_type l) {_l = l;}
private:
    worry_type _l;
};

class monkey {
public:
    monkey(){};
    monkey(std::function<worry_type(worry_type)> f, int d, int y, int n, std::set<int> s) : _f(f),_d(d),_y(y),_n(n),_s(s) {}
    void setf(std::function<worry_type(worry_type)> f) {_f = f;}
    int inspect(banana& b) {
        // b.setl(_f(b.getl())/3);
        // auto aa = b.getl();
        // b.setl(_f(b.getl()%96577));
        // if (b.getl() < 0)
        // {
        //     std::cout << "1:" << aa << std::endl;
        //     std::cout << "2:" << (aa % 96577ll) << std::endl;
        //     std::cout << "3:" << _f(aa % 96577ll) << std::endl;
        //     std::cout << "4:" << b.getl() << std::endl;
        // }
        b.setl(_f(b.getl())%9699690);
        // std::cout << "the item worry level be " << b.getl() << '\n';
        return (b.getl()%_d)?_n:_y;
    }
    void add(int x) {
        _s.insert(x);
    }
    void sets(std::set<int> s) {
        _s = s;
    }
    std::set<int>& gets() {
        return _s;
    }
private:
    std::function<worry_type(worry_type)> _f;
    std::set<int> _s;
    int _d;
    int _y;
    int _n;
};

int main(int argc, char const *argv[])
{
    std::ifstream ifs("day11.txt");
    if (!ifs.is_open())
        return -1;
    std::map<int, int> si;
    std::vector<banana> vec_b;
    std::vector<monkey> vec_m;
    int d,y,n,i,j=0;
    std::set<int> s;
    for (std::string line;std::getline(ifs, line);)
    {
        if (line.size()<1)
        {
            vec_m.push_back(monkey([](int o){return 0;}, d, y, n, s));
            s.clear();
        }
        else if (line.substr(0,6)=="Monkey")
        {
            i=std::stoi(line.substr(7,line.length()-8));
        } 
        else if (line.substr(0,16)=="  Starting items")
        {
            auto tmp = line.substr(18);
            auto first = tmp.begin(), last = tmp.end();
            while (true)
            {
                auto it = find(first, last, ',');
                vec_b.push_back(banana(std::stoi(std::string(first, it))));
                // hold[j++]=i;
                s.insert(j++);
                if(it==last)
                    break;
                first = it + 2;
            }
        }
        else if (line.substr(0,20) == "  Test: divisible by")
        {
            d=std::stoi(line.substr(21));
        }
        else if (line.substr(0,28) == "    If true: throw to monkey")
        {
            y=std::stoi(line.substr(29));
        }
        else if (line.substr(0,29) == "    If false: throw to monkey")
        {
            n=std::stoi(line.substr(30));
        }
    }
    // vec_m[0].setf([](worry_type x)->worry_type { return x * 19;});
    // vec_m[1].setf([](worry_type x)->worry_type { return x + 6;});
    // vec_m[2].setf([](worry_type x)->worry_type { return x * x;});
    // vec_m[3].setf([](worry_type x)->worry_type { return x + 3;});
    vec_m[0].setf([](worry_type x)->worry_type { return x * 3;});
    vec_m[1].setf([](worry_type x)->worry_type { return x * 19;});
    vec_m[2].setf([](worry_type x)->worry_type { return x + 2;});
    vec_m[3].setf([](worry_type x)->worry_type { return x * x;});
    vec_m[4].setf([](worry_type x)->worry_type { return x + 8;});
    vec_m[5].setf([](worry_type x)->worry_type { return x + 6;});
    vec_m[6].setf([](worry_type x)->worry_type { return x + 7;});
    vec_m[7].setf([](worry_type x)->worry_type { return x + 4;});
    for (auto& x:vec_m)
    {
        for (auto& y:x.gets())
            std::cout << y << ", ";
        std::cout << '\n';
    }
    int k = 1;
    int z=10000;
    while (z--)
    {
        std::cout << (k++) << "\n";
        int jj = 0;
        for (auto &x : vec_m)
        {
            std::set<int> tmp;
            for (auto &y : x.gets())
            {
                vec_m[x.inspect(vec_b[y])].add(y);
                si[jj]++;
            }
            x.gets().clear();
            ++jj;
        }
        jj = 0;
        // for (auto &x : vec_m)
        // {
        //     std::cout << jj << ": ";
        //     for (auto &y : x.gets())
        //         std::cout << vec_b[y].getl() << ", ";
        //     std::cout << '\n';
        //     ++jj;
        // }
    }
    for (auto j : si)
    {
        std::cout << j.first << ", " << j.second << '\n';
    }
    ifs.close();
    return 0;
}
