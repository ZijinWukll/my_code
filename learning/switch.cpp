#include <iostream>
int main()
{
    int op;
    std::cin >> op;
    switch (op)
    {
    case 1:
        std::cout << "a";
        break;
    case 2:
        std::cout << "b";
        break;
    default:
        std::cout << "c";
        break;
    }
    return 0;
}