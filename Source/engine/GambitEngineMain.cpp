#include <iostream>
#include "Base/GambitBaseTest.h"
#include "Base/LoggerManager/LoggerManager.h"

class A
{

};

int main()
{
    std::cout << "Attempting to call GambitBase API...\n";
    gb::CallExample();

    gb::LoggerManager lm;

    lm.Log("{} This {} is a {} test {}.", 32, "Robert", 45.6f);

    system("pause");
    return 0;
}