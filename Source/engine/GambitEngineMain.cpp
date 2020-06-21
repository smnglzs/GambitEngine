#include <iostream>
#include "Base/GambitBaseModule.h"
#include "Base/LoggerManager/LoggerManager.h"

int main()
{
    std::cout << "Attempting to call GambitBase API...\n";
    gb::ModuleBase gbMod;

    gbMod.RegisterSingletons();
    gbMod.StartUp();
    gbMod.ShutDown();

    system("pause");
    return 0;
}