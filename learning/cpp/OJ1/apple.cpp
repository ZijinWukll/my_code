#include <iostream>

int main()
{
    int height[10];
    for (int i = 0; i < 10; i++)
    {
        std::cin >> height[i];
    }
    int tao;
    std::cin >> tao;
    int total = tao + 30;
    int number = 0;
    for (int i = 0; i < 10; i++)
    {
        if (height[i] <= total)
            number++;
    }
    std::cout << number;
    return 0;
}