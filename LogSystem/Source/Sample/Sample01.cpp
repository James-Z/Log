#include "../LogSystem.h"

//
int main()
{
    std::string str("This ");
    Log(str.c_str(), "is a Log");
    LogWarn("This is a Log");
    LogError("This is a Log, Error local ", __CODELOCAL__);

    //
    SetLogFilePath("../Log/");

    FLog(str.c_str(), "is ", 1, " File Log");
    float fvalue = 1.0F;
    FLogWarn("This is ", fvalue, " File Log");
    FLogError("This is a File Log, Error local ", __CODELOCAL__);

    //
    std::cin.get();
    return 0;
}