#include <iostream>

#include <time.h>

#include "MenuUI.h"

int main()
{
    clock_t start = clock();
    //CreateData();

    std::cout << "��ȡ�����С�����������" << std::endl;
    if (!Init())
    {
        std::cout << "��ʼ��ʧ��" << std::endl;
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