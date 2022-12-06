#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <set>
#include <stack>

using namespace std;

int main(int argc, char** argv) {
    vector<stack<char>> stacks(9, stack<char>());
    {
        ifstream ifs1("input1.txt");
        if (!ifs1.is_open())
            return -1;
        vector<string> memo;
        for(string line; getline(ifs1, line);) memo.push_back(line);
        for (auto first = memo.rbegin(); first != memo.rend(); ++first)
        {
            for (int i = 1; i < 34; i += 4)
            {
                if ((*first)[i] != ' ')
                    stacks[i / 4].push((*first)[i]);
            }
        }
    }
    {
        ifstream ifs2("input2.txt");
        if (!ifs2.is_open())
            return -1;
        for (string line; getline(ifs2, line);)
        {
            auto first = line.begin();
            auto last = line.end();
            auto first2 = find(first, last, ' ');
            auto first3 = find(first2 + 1, last, ' ');
            int n = stoi(string(first, first2)), from = stoi(string(first2 + 1, first3)) - 1, to = stoi(string(first3 + 1, last)) - 1;
            stack<char> tmp;
            while (n--)
            {
                assert(!stacks.empty() && "cannot be empty");
                tmp.push(stacks[from].top());
                stacks[from].pop();
            }
            while (!tmp.empty())
            {
                stacks[to].push(tmp.top());
                tmp.pop();
            }
        }
        for (auto m : stacks)
            cout << m.top();
        cout << endl;

    }
    return 0;
}