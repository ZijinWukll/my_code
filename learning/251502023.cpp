#include <iostream>
#include <cstring>
using namespace std;

// 用结构体封装动态数组
struct DynArray
{
    int *data;
    int size, cap;
    DynArray()
    {
        data = nullptr;
        size = 0;
        cap = 0;
    }
    ~DynArray()
    {
        delete[] data;
    }
    void add(int val)
    {
        if (size >= cap)
        {
            int newcap = cap == 0 ? 2 : cap * 2;
            int *tmp = new int[newcap];
            if (data)
                memcpy(tmp, data, sizeof(int) * size);
            delete[] data;
            data = tmp;
            cap = newcap;
        }
        data[size++] = val;
    }
};

int main()
{
    DynArray arr;
    int x;
    while (cin >> x && x != -1)
    {
        arr.add(x);
    }
    for (int i = 0; i < arr.size; ++i)
        cout << arr.data[i] << " ";
    cout << endl;
    return 0;
}
