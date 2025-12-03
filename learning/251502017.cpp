#include <iostream>
using namespace std;

// 插入元素并自动扩容的函数
// arr: 指向动态数组的指针的指针（用于扩容时修改主指针）
// size: 当前元素个数的指针
// capacity: 当前容量的指针
// val: 要插入的值
void push_back(int **arr, int *size, int *capacity, int val)
{
    // 如果当前元素个数达到容量，则需要扩容
    if (*size >= *capacity)
    {
        // 扩容：容量翻倍，初始容量为2
        int new_capacity = (*capacity == 0) ? 2 : (*capacity * 2);
        int *new_arr = new int[new_capacity]; // 新建更大的数组
        // 把原数组内容拷贝到新数组
        for (int i = 0; i < *size; i++)
            new_arr[i] = (*arr)[i];
        delete[] *arr;            // 释放原数组空间，防止内存泄漏
        *arr = new_arr;           // 更新主指针，指向新数组
        *capacity = new_capacity; // 更新容量
    }
    // 插入新元素到数组末尾
    (*arr)[(*size)++] = val;
}

int main()
{
    int *arr = nullptr;         // 动态数组指针，初始为空
    int size = 0, capacity = 0; // 当前元素个数和容量
    int x;
    // 循环读入数据，-1表示输入结束
    while (cin >> x && x != -1)
    {
        // 插入元素，自动扩容
        push_back(&arr, &size, &capacity, x);
    }
    // 输出所有元素
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
    delete[] arr; // 释放动态数组，防止内存泄漏
    return 0;
}
