#include <iostream>
#include "Base/GambitBaseTest.h"
#include "Base/LoggerManager/LoggerManager.h"

int main()
{
    std::cout << "Attempting to call GambitBase API...\n";
    gb::CallExample();

    gb::LoggerManager lm;
    gb::LogChannel channel{ "Test", gb::EOutputType::Both, gb::ELogLevel::Info, "Text.txt" };

    lm.AddChannel("Test", channel);

    lm.Log("Test", "{} This {} is a {} test {}.", 32, "Hello", 4.5f);

    system("pause");
    return 0;
}