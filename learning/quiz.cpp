#include <iostream>
int main()
{
    int a = 2, b = 5;
    int t = (a++ + b) / 2;
    double y = t + (double)b / a;
    std::cout << t << " " << y << " " << a << " " << b;
}