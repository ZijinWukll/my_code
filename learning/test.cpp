#include <iostream>
#include <set>
#include <map>
using namespace std;
int main()
{
    set<int> s;
    s.insert(100);
    s.insert(2);
    s.insert(5);
    s.insert(3);
    for (auto it : s)
    {
        cout << it << " ";
    }
    pair<string, int> me;
    me.first = "dtr";
    me.second = 18; // pair类型
    // 枚举类型
    enum date
    {
        sun,
        mon,
        tue,
        wed,
        thu,
        fri,
        sat
    };
    date d1 = sun;
    date d2 = mon;
    // map:键值对的汇集（key ，value）类似于字典
    map<string, string> contact;
    contact["hdwuehd"] = "21343";
    contact["hdwue"] = "213";
    cout << contact["hdwuehd"];
    return 0;
}