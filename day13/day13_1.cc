#include <iostream>
#include <fstream>
#include <vector>

typedef std::string::iterator it_type;
class st {
public:
    st(it_type first, it_type last):_first(first),_last(last){}
    st get_next() {
        if (*_first=='[')
            ++_first;
        it_type i1(_first);
        int c(0);
        while (_first!=_last)
        {
            if (*_first=='[')
            {
                ++c;
            }
            else if (*_first==']')
            {
                if (c--==0) return st(i1,_first++);
            }
            else if (*_first==',')
            {
                if (c==0) return st(i1,_first++);
            }
            ++_first;
        }
        return st(_last,_last);
    }
    int has_next() {
        return _first==_last?0:1;
    }
    int is_val() {
        if (_first==_last)
            return 0;
        if (*(_last-1)==']')
            return 0;
        return 1;
    }
    int val() {
        return stoi(std::string(_first,_last));
    }
    std::string to_string() {
        return std::string(_first,_last);
    }
    friend std::ostream &operator<<(std::ostream &os, st &s) {
        return os << s.to_string();
    }
private:
    it_type _first, _last;
};


int compare(st& s1, st& s2) {
    // std::cout << "compare " << s1 << ", " << s2 << '\n';
    if (!s1.has_next())
        return s2.has_next()?-1:0;
    if (!s2.has_next())
        return 1;
    auto x1(s1.get_next()),x2(s2.get_next());
    if (x1.is_val()&&x2.is_val())
    {
        auto y1(x1.val()),y2(x2.val());
        if (y1<y2)
            return -1;
        if (y1>y2)
            return 1;
    }
    else if (x1.is_val())
    {
        std::string tmp = "[" + x1.to_string() + "]";
        st s(tmp.begin(),tmp.end());
        auto p = compare(s,x2);
        if (p) return p;
    }
    else if (x2.is_val())
    {
        std::string tmp = "[" + x2.to_string() + "]";
        st s(tmp.begin(),tmp.end());
        auto p = compare(x1,s);
        if (p) return p;
    }
    else
    {
        auto p = compare(x1,x2);
        if (p) return p;
    }
    return compare(s1,s2);
}

int main(int argc, char const *argv[])
{
    std::ifstream ifs("day13.txt");
    if (!ifs.is_open())
        return -1;
    int c(0),res(0);
    for (std::string line;std::getline(ifs,line);)
    {
        c++;
        st s1(line.begin(),line.end());
        std::string line2;
        std::getline(ifs, line2);
        st s2(line2.begin(),line2.end());
        auto p = compare(s1,s2);
        if (p<1)
            res+=c;
        std::string line3;
        std::getline(ifs, line3);
        // std::cout << line << " vs. " << line2 << " " << p << std::endl;
        // break;
    }
    std::cout << res << '\n';
    ifs.close();
    return 0;
}
