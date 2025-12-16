#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct three
{ // 一种方案的三个位置人数
    int fang;
    int zhong;
    int jin;
};
struct player // 球员信息
{
    string nengli;
    int bianhao; // 考虑7种不同组合的能力分别编号？？
};

int main()
{
    vector<three> coach; // 容器储存n个方案
    int n, m;
    cin >> n;
    string line;
    getline(cin, line); // consume end of line after n
    for (int i = 0; i < n; i++)
    {
        three temp;
        // read a non-empty line that may look like: "12-34-56" or "12 34 56"
        do
        {
            if (!getline(cin, line))
                line = "";
            // if line is empty (blank line), try again
        } while (line.size() == 0);

        // replace '-' with spaces so stringstream can parse integers
        for (char &c : line)
            if (c == '-')
                c = ' ';

        stringstream ss(line);
        // try to parse three integers
        if (!(ss >> temp.fang >> temp.zhong >> temp.jin))
        {
            // parsing failed — set defaults to 0
            temp.fang = temp.zhong = temp.jin = 0;
        }
        coach.push_back(temp);
    }

    cin >> m;
    vector<player> Player;
    int one = 0;
    int two = 0;
    int three = 0;
    int four = 0;
    int five = 0;
    int six = 0;
    int seven = 0;
    for (int i = 0; i < m; i++)
    {
        player temp; // 分类
        cin >> temp.nengli;
        if (temp.nengli == "O")
        {
            temp.bianhao = 1;
            one++;
        }
        if (temp.nengli == "V")
        {
            temp.bianhao = 2;
            two++;
        }
        if (temp.nengli == "N")
        {
            temp.bianhao = 3;
            three++;
        }
        if (temp.nengli == "OV" || temp.nengli == "VO")
        {
            temp.bianhao = 4;
            four++;
        }
        if (temp.nengli == "ON" || temp.nengli == "NO")
        {
            temp.bianhao = 5;
            five++;
        }
        if (temp.nengli == "VN" || temp.nengli == "NV")
        {
            temp.bianhao = 6;
            six++;
        }
        if (temp.nengli == "OVN" || temp.nengli == "ONV" || temp.nengli == "NOV" || temp.nengli == "NVO" || temp.nengli == "VON" || temp.nengli == "VNO")
        {
            temp.bianhao = 7;
            seven++;
        }
        Player.push_back(temp);
    }

    for (int i = 0; i < n; i++) // 想知道这里用bool怎么写？
    {
        // 算法没问题
        if (coach[i].fang <= one + four + five + seven && coach[i].zhong <= two + four + six + seven && coach[i].jin <= three + five + six + seven && coach[i].fang + coach[i].zhong <= one + two + four + five + six + seven && coach[i].zhong + coach[i].jin <= two + three + four + five + six + seven && coach[i].fang + coach[i].jin <= one + three + four + five + six + seven)
        {
            cout << "DA" << endl;
        }
        else
        {
            cout << "NE" << endl;
        }
    }
    return 0;
}
