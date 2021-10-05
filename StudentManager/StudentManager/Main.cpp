#include <iostream>

#include <time.h>

#include "MenuUI.h"

int main()
{
    clock_t start = clock();
    //CreateData();

    std::cout << "读取数据中。。。。。。" << std::endl;
    if (!Init())
    {
        std::cout << "初始化失败" << std::endl;
        return 0;
    }

    clock_t end = clock();

    int startTime = end - start;

    while (true)
    {
        ShowMenu();
    }

    return 0;
}