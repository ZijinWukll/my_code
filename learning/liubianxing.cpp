#include <iostream>
using namespace std;

void firstlast(int n)
{
    for (int j = 0; j < n; j++)
    {
        cout << " ";
    }
    cout << "+";
    for (int j = 0; j < 2 * n + 1; j++)
    {
        cout << "-";
    }
    cout << "+" << endl;
}
void lineup(int line_i, int n)
{
    for (int j = 0; j < n - line_i + 1; j++)
    {
        cout << " ";
    }
    cout << "/";
    for (int j = 0; j < 2 * n + 2 * line_i - 1; j++)
    {
        cout << " ";
    }
    cout << "\\" << endl;
}
void middle(int n)
{
    cout << "+";
    for (int j = 0; j < 4 * n + 1; j++)
    {
        cout << " ";
    }
    cout << "+" << endl;
}
void linedown(int line_i, int n)
{
    for (int j = 0; j < line_i - n - 1; j++)
    {
        cout << " ";
    }
    cout << "\\";
    for (int j = 0; j < 6 * n - 2 * line_i + 3; j++)
    {
        cout << " ";
    }
    cout << "/" << endl;
}

int main()
{
    int n;
    cin >> n;
    firstlast(n);
    for (int i = 2; i < n + 1; i++)
    {
        lineup(i, n);
    }
    middle(n);
    for (int i = n + 2; i < 2 * n + 1; i++)
    {
        linedown(i, n);
    }
    firstlast(n);
    return 0;
}