#include <iostream>
using namespace std;

struct node // 一个节点
{
    int value;
    struct node *next;
};

// malloc函数创建一个动态内存，保留在电脑里,但是c++可以用new
node *create_list()
{
    node *p, *head, *tail; // p是一个活动的指针
    p = new node();
    head = p;
    tail = p;
    tail->next = NULL;
    for (int i = 0; i < 10; i++)
    {
        p = new node();
        cin >> p->value;
        tail->next = p;
        tail = p;
        tail->next = NULL;
    }
    return head;
}
// 插入节点
void insert_node(node *head, int position, int value)
{                   // 明确插入位置和值，要知道该链表的头节点
    node *p = head; // 活动元素p遍历链表
    for (int i = 0; i < position; i++)
    {
        if (p == NULL)
            return;
        p = p->next;
    } // for循环定位到position位置
    node *new_node = new node();
    new_node->value = value;  // 创造新节点，赋值
    new_node->next = p->next; // next挂上后面的链表
    p->next = new_node;       // 接到前面的链表里
}

// 删除节点
void delete_node(node *head, int position)
{
    node *p = head;
    for (int i = 0; i < position - 1; i++) // 注意位置！
    {
        if (p->next == NULL)
            return;
        p = p->next;
    }
    node *to_delete = p->next;
    if (to_delete == NULL)
        return;
    p->next = to_delete->next;
    delete to_delete;
}

int main()
{
    node *head = create_list();
    node *p = head->next;
    delete_node(head, 4);
    while (p != NULL)
    {
        cout << p->value << " ";
        p = p->next;
    }
    return 0;
}